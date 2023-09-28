#include "Generator.hpp"
#include "Event/PositiveEvents/Potion.hpp"
#include "Event/MovementEvents/RandomMine.hpp"
#include "Event/NegativeEvents/Spikes.hpp"
#include "Random/Random.hpp"
#include <set>
#include <random>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <map>

Map *Generator::generate()
{
	auto engine = Random::get_instance();

	Map *map = new Map(m_, n_);

	for (int32_t i = 0; i < map->get_dimensions().get_x(); i++)
	{
		for (int32_t j = 0; j < map->get_dimensions().get_y(); j++)
		{
			map->build_wall({i, j});
		}
	}

	generate_maze(map);

	std::vector<Position> movable_cells;

	for (int32_t i = 0; i < map->get_dimensions().get_x(); i++)
	{
		for (int32_t j = 0; j < map->get_dimensions().get_y(); j++)
		{
			Position cur_point(i, j);
			if (!map->get_cell(cur_point).is_movable())
			{
				continue;
			}
			movable_cells.emplace_back(cur_point);
		}
	}
	for (auto &cell: movable_cells)
	{
		if (cell.get_x() * 4 < map->get_dimensions().get_x() && cell.get_y() * 2 < map->get_dimensions().get_y())
		{
			map->reset_start(cell);
			break;
		}
	}
	for (auto &cell: movable_cells)
	{
		if (cell.get_x() * 4 / 3 >= map->get_dimensions().get_x()
			&& cell.get_y() * 4 / 3 >= map->get_dimensions().get_y())
		{
			map->reset_finish(cell);
			break;
		}
	}

	auto route = find_route(map);

	for (auto &cell: route)
	{
		map->get_cell(cell).add_event(new Potion);
	}

	// TODO place events
	// note that spikes events on the route must be at most 4(5)

	/*movable_cells.erase(std::find(movable_cells.begin(), movable_cells.end(), map->get_start_point()));
	movable_cells.erase(std::find(movable_cells.begin(), movable_cells.end(), map->get_finish_point()));
	std::shuffle(movable_cells.begin(), movable_cells.end(), std::mt19937(std::random_device()()));

	auto events = generate_events(std::min(static_cast<int32_t>(movable_cells.size()),
										   num_positive_ + num_negative_ + num_other_));
	std::shuffle(events.begin(), events.end(), std::mt19937(std::random_device()()));

	std::cerr << events.size() << std::endl;

	for (int32_t i = 0; i < events.size(); ++i)
	{
		map->get_cell(movable_cells[i]).add_event(events[i]);
	}*/

	return map;
}
Generator::Generator(int32_t m, int32_t n, int32_t total_events, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent) : m_(m),
																																								   n_(n)
{
	int32_t cells_available = m_ * n_ - 2;

	total_events = std::min(cells_available * 7 / 10, total_events);
	total_events = std::max(0, total_events);

	if (positive_events_percent + negative_events_percent + other_events_percent > 100)
	{
		positive_events_percent = 50;
		negative_events_percent = 30;
		other_events_percent = 20;
	}

	num_positive_ = static_cast<int32_t>(total_events * 1.0 * positive_events_percent / 100.0);
	num_negative_ = static_cast<int32_t>(total_events * 1.0 * negative_events_percent / 100.0);
	num_other_ = static_cast<int32_t>(total_events * 1.0 * other_events_percent / 100.0);
}
std::vector<EventInterface *> Generator::generate_events(int32_t lim) const
{
	std::vector<EventInterface *> events;
	events.reserve(lim);

	std::vector<int32_t> events_count = {num_negative_, num_other_, num_positive_};

	while (events.size() < lim)
	{
		for (int16_t i = 0; i < events_count.size(); ++i)
		{
			if (events.size() < lim && events_count[i] > 0)
			{
				events_count[i]--;
				events.push_back(Random::get_instance().pick_event(static_cast<EVENT_TYPE>(i - 1)));
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

void add_walls(Map *map, const Position &position, std::vector<Wall> &walls)
{
	for (int16_t dir = UP; dir <= LEFT; dir += 1)
	{
		if (auto wall_pos = Direction::getInstance().calculate_position(position, static_cast<DIRECTION>(dir)), neighbour = Direction::getInstance().calculate_position(wall_pos, static_cast<DIRECTION>(dir));
			map->is_on_map(wall_pos) && !map->get_cell(wall_pos).is_movable() && map->is_on_map(neighbour)
			&& !map->get_cell(neighbour).is_movable())
		{
			walls.push_back({wall_pos, position, neighbour});
		}
	}
}

// Iterative randomized Prim's algorithm
// https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_randomized_Prim's_algorithm_(without_stack,_without_sets)
void Generator::generate_maze(Map *map)
{
	auto engine = Random::get_instance();
	std::vector<Wall> walls;
	std::unordered_set<int32_t> visited;

	int i = engine.pick_num(0, map->get_dimensions().get_x() - 1);
	int j = engine.pick_num(0, map->get_dimensions().get_y() - 1);

	map->destroy_wall({i, j});

	// Add the walls of the cell to the wall list
	add_walls(map, {i, j}, walls);

	// While there are walls in the list
	while (!walls.empty())
	{
		// Pick a random wall from the list
		auto index = engine.pick_num(0, walls.size() - 1);
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
std::vector<Position> Generator::find_route(Map *map_)
{
	auto start = map_->get_start_point();
	auto end = map_->get_finish_point();

	int m = map_->get_dimensions().get_x();
	int n = map_->get_dimensions().get_y();
	std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
	std::map<Position, Position> prev;
	std::vector<Position> directions{{-1, 0},
									 {1,  0},
									 {0,  -1},
									 {0,  1}};
	std::queue<Position> q;

	visited[start.get_x()][start.get_y()] = true;
	q.push(start);

	while (!q.empty())
	{
		auto current = q.front();
		q.pop();

		if (current == end)
		{
			break;
		}

		for (auto &direction: directions)
		{
			auto new_pos = current + direction;

			if (map_->can_move(new_pos) && !visited[new_pos.get_x()][new_pos.get_y()])
			{
				q.push(new_pos);
				visited[new_pos.get_x()][new_pos.get_y()] = true;
				prev[new_pos] = current;
			}
		}
	}

	std::vector<Position> path;

	for(Position it = end; it != start; it = prev[it])
	{
		path.push_back(it);
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());

	return path;
}
