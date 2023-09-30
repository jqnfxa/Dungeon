#include "Generator.hpp"
#include "Random/Random.hpp"
#include <set>
#include <random>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <utility>

GameField *Generator::generate()
{
	// generate maze
	auto *map = new GameField(m_, n_);
	generate_maze(map);

	std::set<Position> movable_cells = get_all_movable_cells(map);

	// reset start and finish
	reset_points(movable_cells, map);

	// calculate event distribution
	calculate_percentages(static_cast<int32_t>(movable_cells.size()));

	place_spikes_on_route(movable_cells, map, 4);

	std::vector<Position> movable_cells_(movable_cells.begin(), movable_cells.end());

	auto num_remained_events = std::min(static_cast<int32_t>(movable_cells_.size()),
										num_negative_ + num_positive_ + num_other_);
	auto remained_events = generate_events(num_remained_events, {num_negative_, num_other_, num_positive_});
	std::shuffle(movable_cells_.begin(), movable_cells_.end(), std::mt19937(std::random_device()()));
	std::shuffle(remained_events.begin(), remained_events.end(), std::mt19937(std::random_device()()));

	for (size_t j = 0, i = 0; j < movable_cells_.size() && i < remained_events.size(); ++j)
	{
		if (!map->is_adjacent_to_same_type(movable_cells_[j]))
		{
			map->get_cell(movable_cells_[j]).add_event(remained_events[i++]);
		}
	}
	return map;
}

Generator::Generator(int32_t m,
					 int32_t n,
					 int32_t total_percent,
					 int32_t positive_events_percent,
					 int32_t negative_events_percent,
					 int32_t other_events_percent) :
					 m_(m),
					 n_(n),
					 total_percent(total_percent),
					 num_positive_(positive_events_percent),
					 num_negative_(negative_events_percent),
					 num_other_(other_events_percent)
{
}

std::vector<EventInterface *> Generator::generate_events(int32_t lim, std::vector<int> events_count) const
{
	std::vector<EventInterface *> events;
	events.reserve(lim);

	while (events.size() < lim)
	{
		for (size_t i = 0; i < events_count.size(); ++i)
		{
			if (events.size() < lim && events_count[i] > 0)
			{
				events_count[i]--;
				events.push_back(Random::instance().pick_event(static_cast<EVENT_GROUP>(i - 1)));
			}
		}
	}
	return events;
}

void Generator::add_walls(GameField *map, const Position &position, std::vector<Wall> &walls)
{
	for (auto &direction: Direction::instance().get_all_possible_moves())
	{
		if (auto wall_pos = position + direction, neighbour = wall_pos + direction;
			map->is_on_map(wall_pos) && !map->get_cell(wall_pos).is_movable() && map->is_on_map(neighbour)
			&& !map->get_cell(neighbour).is_movable())
		{
			walls.push_back({wall_pos, position, neighbour});
		}
	}
}

// Iterative randomized Prim's algorithm
// https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_randomized_Prim's_algorithm_(without_stack,_without_sets)
void Generator::generate_maze(GameField *map)
{
	auto engine = Random::instance();

	// fill map with walls first
	for (int32_t i = 0; i < map->dimensions().x(); ++i)
	{
		for (int32_t j = 0; j < map->dimensions().y(); ++j)
		{
			map->build_wall({i, j});
		}
	}

	std::vector<Wall> walls;
	std::unordered_set<int32_t> visited;

	int i = engine.pick_num(0, map->dimensions().x() - 1);
	int j = engine.pick_num(0, map->dimensions().y() - 1);

	map->destroy_wall({i, j});

	// Add the walls of the cell to the wall list
	add_walls(map, {i, j}, walls);

	// While there are walls in the list
	while (!walls.empty())
	{
		// Pick a random wall from the list
		auto index = engine.pick_num(0, static_cast<int32_t>(walls.size() - 1));
		auto wall = walls[index];
		walls.erase(walls.begin() + index);

		// If only one of the cells that the wall divides is visited
		if (map->get_cell(wall.cell1).is_movable() != map->get_cell(wall.cell2).is_movable())
		{
			// Make the wall a passage and mark the unvisited cell as part of the maze
			map->destroy_wall(wall.pos);

			if (!map->get_cell(wall.cell1).is_movable())
			{
				map->destroy_wall(wall.cell1);
				add_walls(map, wall.cell1, walls);
			}
			else if (!map->get_cell(wall.cell2).is_movable())
			{
				map->destroy_wall(wall.cell2);
				add_walls(map, wall.cell2, walls);
			}
		}
	}
}

std::set<Position> Generator::get_all_movable_cells(GameField *map)
{
	std::set<Position> movable_cells;

	if (map != nullptr)
	{
		for (int32_t i = 0; i < map->dimensions().x(); ++i)
		{
			for (int32_t j = 0; j < map->dimensions().y(); ++j)
			{
				Position cur_point(i, j);
				if (!map->get_cell(cur_point).is_movable())
				{
					continue;
				}
				movable_cells.insert(std::move(cur_point));
			}
		}
	}

	return movable_cells;
}

Position Generator::pick_random_empty_cell(std::set<Position> &movable_cells, std::function<bool(const Position &)> criteria)
{
	std::vector<Position> possible_cells;

	std::copy_if(movable_cells.begin(), movable_cells.end(), std::back_inserter(possible_cells), std::move(criteria));
	return Random::instance().pick_from_range(possible_cells.begin(), possible_cells.end());
}

void Generator::reset_points(std::set<Position> &movable_cells, GameField *map)
{
	auto start_point = pick_random_empty_cell(movable_cells, [&](const Position &position)
	{
		return position.x() * 4 < map->dimensions().x() && position.y() * 4 < map->dimensions().y();
	});

	map->reset_start(start_point);
	movable_cells.erase(start_point);

	auto end_point = pick_random_empty_cell(movable_cells, [&](const Position &position)
	{
		return position.x() * 4 / 3 >= map->dimensions().x() && position.y() * 4 / 3 >= map->dimensions().y();
	});

	map->reset_finish(end_point);
	movable_cells.erase(end_point);
}

void Generator::calculate_percentages(int32_t total_movable_cells)
{
	auto cells_available = static_cast<double>(total_movable_cells);
	auto total_events = static_cast<int32_t>(cells_available * total_percent / 100);

	if (num_positive_ + num_negative_ + num_other_ > 100)
	{
		num_positive_ = positive_default;
		num_negative_ = negative_default;
		num_other_ = other_default;
	}

	num_positive_ = static_cast<int32_t>(total_events * 1.0 * num_positive_ / 100.0);
	num_negative_ = static_cast<int32_t>(total_events * 1.0 * num_negative_ / 100.0);
	num_other_ = static_cast<int32_t>(total_events * 1.0 * num_other_ / 100.0);
}

void Generator::place_spikes_on_route(std::set<Position> &movable_cells, GameField *map, int32_t at_most)
{
	// build route from start to finish
	auto route = map->find_route(map->start_point(), map->exit_point());

	// add spikes on route
	auto spikes_on_route = generate_events(std::min(num_negative_, at_most), {std::min(num_negative_, at_most), 0, 0});
	num_negative_ = std::max(0, num_negative_ - at_most);

	std::shuffle(route.begin(), route.end(), std::mt19937(std::random_device()()));

	for (size_t i = 0; i < spikes_on_route.size(); ++i)
	{
		map->get_cell(route[i]).add_event(spikes_on_route[i]);
	}

	// delete route path from movable cells to prevent bad event distribution
	for (auto &cell: route)
	{
		movable_cells.erase(cell);
	}
}
