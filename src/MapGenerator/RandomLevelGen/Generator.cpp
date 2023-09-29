#include "Generator.hpp"
#include "Random/Random.hpp"
#include <set>
#include <random>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <map>

GameField *Generator::generate()
{
	auto engine = Random::instance();

	GameField *map = new GameField(m_, n_);

	for (int32_t i = 0; i < map->dimensions().x(); i++)
	{
		for (int32_t j = 0; j < map->dimensions().y(); j++)
		{
			map->build_wall({i, j});
		}
	}

	generate_maze(map);

	std::set<Position> movable_cells;

	for (int32_t i = 0; i < map->dimensions().x(); i++)
	{
		for (int32_t j = 0; j < map->dimensions().y(); j++)
		{
			Position cur_point(i, j);
			if (!map->get_cell(cur_point).is_movable())
			{
				continue;
			}
			movable_cells.insert(std::move(cur_point));
		}
	}

	std::vector<Position> possible_start;
	std::vector<Position> possible_end;

	std::copy_if(movable_cells.begin(), movable_cells.end(), std::back_inserter(possible_start), [&](const Position &position)
	{
		return position.x() * 4 < map->dimensions().x() && position.y() * 4 < map->dimensions().y();
	});
	movable_cells.erase(map->start_point());
	std::copy_if(movable_cells.begin(), movable_cells.end(), std::back_inserter(possible_end), [&](const Position &position)
	{
		return position.x() * 4 / 3 >= map->dimensions().x() && position.y() * 4 / 3 >= map->dimensions().y();
	});

	map->reset_start(engine.pick_from_range(possible_start.begin(), possible_start.end()));
	map->reset_finish(engine.pick_from_range(possible_end.begin(), possible_end.end()));

	auto route = find_route(map);

	/*
	Map *copy = new Map(*map);

	for (auto &cell : route)
	{
		copy->get_cell(cell).add_event(new Potion);
	}

	copy->print(std::cerr);

	delete copy;
	*/

	auto cells_available = static_cast<double>(movable_cells.size());
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

	// add spikes on route
	auto spikes_on_route = generate_events(std::min(num_negative_, 4), {std::min(num_negative_, 4), 0, 0});
	num_negative_ = std::max(0, num_negative_ - 4);

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

	std::vector<Position> movable_cells_(movable_cells.begin(), movable_cells.end());

	auto remained_events = generate_events(std::min(static_cast<int32_t>(movable_cells_.size()),
													num_negative_ + num_positive_ + num_other_), {num_negative_,
																								  num_other_,
																								  num_positive_});
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
Generator::Generator(int32_t m, int32_t n, int32_t total_percent, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent) : m_(m),
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

struct Wall {
	Position pos;
	Position cell1;
	Position cell2;
};

void add_walls(GameField *map, const Position &position, std::vector<Wall> &walls)
{
	for (auto &direction : Direction::instance().get_all_possible_moves())
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
std::vector<Position> Generator::find_route(GameField *map_)
{
	const auto &start = map_->start_point();
	const auto &end = map_->exit_point();

	int m = map_->dimensions().x();
	int n = map_->dimensions().y();
	std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
	std::map<Position, Position> prev;
	std::queue<Position> q;

	visited[start.x()][start.y()] = true;
	q.push(start);

	while (!q.empty())
	{
		auto current = q.front();
		q.pop();

		if (current == end)
		{
			break;
		}

		for (auto &direction: Direction::instance().get_all_possible_moves())
		{
			auto new_pos = current + direction;

			if (map_->can_move(new_pos) && !visited[new_pos.x()][new_pos.y()])
			{
				q.push(new_pos);
				visited[new_pos.x()][new_pos.y()] = true;
				prev[new_pos] = current;
			}
		}
	}

	std::vector<Position> path;

	for (Position it = end; it != start; it = prev[it])
	{
		path.push_back(it);
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());

	return path;
}
