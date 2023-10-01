#include "GameField.hpp"
#include "Movement/Direction.hpp"
#include "Event/MovementEvents/Door.hpp"
#include <ostream>
#include <queue>
#include <map>
#include <vector>

GameField::GameField(const Dimension &dimensions) : dimensions_(dimensions),
													start_(-1, -1),
													finish_(-1, -1),
													map_(nullptr)
{
	if (dimensions_.x() < MAP_DIMENSION_LOWER_BOUND || dimensions_.y() < MAP_DIMENSION_LOWER_BOUND
		|| dimensions_.x() > MAP_DIMENSION_UPPER_BOUND || dimensions_.y() > MAP_DIMENSION_UPPER_BOUND)
	{
		throw std::logic_error("Unexpected dimensions for map (too small or too big)");
	}
	map_ = allocate_map(dimensions_);
}
GameField::GameField(int32_t dim_x, int32_t dim_y) : GameField(Position(dim_x, dim_y))
{
}
GameField::~GameField()
{
	clear_map();
}
GameField::GameField() : GameField(MAP_DIMENSION_LOWER_BOUND, MAP_DIMENSION_LOWER_BOUND)
{
}
GameField::GameField(const GameField &other) : GameField()
{
	swap_values(other);
}
GameField::GameField(GameField &&other) noexcept: GameField()
{
	swap_values(std::move(other));
}
GameField &GameField::operator=(const GameField &other)
{
	if (&other != this)
	{
		swap_values(other);
	}
	return *this;
}
GameField &GameField::operator=(GameField &&other) noexcept
{
	if (&other != this)
	{
		swap_values(std::move(other));
	}
	return *this;
}
void GameField::clear_map()
{
	if (map_ == nullptr)
	{
		return;
	}

	for (int32_t i = 0; i < dimensions_.x(); ++i)
	{
		for (int32_t j = 0; j < dimensions_.y(); ++j)
		{
			map_[i][j].remove_event();
		}
		delete[] map_[i];
	}
	delete[] map_;
	map_ = nullptr;
}
Cell **GameField::allocate_map(const Dimension &dimensions)
{
	auto map = new Cell *[dimensions.x()];

	for (int32_t i = 0; i < dimensions.x(); ++i)
	{
		map[i] = new Cell[dimensions.y()];
	}
	return map;
}
Cell &GameField::get_cell(const Position &point) const
{
	if (!is_on_map(point))
	{
		throw std::out_of_range("Point is out of map");
	}
	return map_[point.x()][point.y()];
}
void GameField::set_cell(const Position &point, Cell &&new_cell)
{
	if (!is_on_map(point))
	{
		return;
	}
	map_[point.x()][point.y()] = std::move(new_cell);
}
void GameField::set_cell(const Position &point, const Cell &new_cell)
{
	if (!is_on_map(point))
	{
		return;
	}
	map_[point.x()][point.y()] = new_cell;
}
const Dimension &GameField::dimensions() const
{
	return dimensions_;
}
void GameField::reset_start(const Position &point)
{
	if (can_move(point))
	{
		if (start_ != Position(-1, -1))
		{
			map_[start_.x()][start_.y()].set_type(Cell::TYPE::MOVABLE);
		}
		start_ = point;
		map_[start_.x()][start_.y()].set_type(Cell::TYPE::ENTRANCE);
	}
}
void GameField::reset_finish(const Vector2<int32_t> &point)
{
	if (can_move(point))
	{
		if (finish_ != Position(-1, -1))
		{
			map_[finish_.x()][finish_.y()].set_type(Cell::TYPE::MOVABLE);
		}
		finish_ = point;
		map_[finish_.x()][finish_.y()].set_type(Cell::TYPE::EXIT);
	}
}
void GameField::build_wall(const Position &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		map_[point.x()][point.y()].set_type(Cell::TYPE::WALL);
	}
}
void GameField::destroy_wall(const Position &point)
{
	if (is_on_map(point) && !get_cell(point).is_movable())
	{
		map_[point.x()][point.y()].set_type(Cell::TYPE::MOVABLE);
	}
}
bool GameField::is_on_map(const Position &point) const
{
	return point.x() >= 0 && point.y() >= 0 && point.x() < dimensions_.x() && point.y() < dimensions_.y();
}
const Position &GameField::start_point() const
{
	return start_;
}
const Position &GameField::exit_point() const
{
	return finish_;
}
std::ostream &GameField::print(std::ostream &out) const
{
	for (int32_t i = 0; i < dimensions_.x(); i++)
	{
		for (int32_t j = 0; j < dimensions_.y(); j++)
		{
			out << get_cell({i, j});
			out << std::flush;
		}
		out << std::endl;
	}
	return out << std::endl;
}
bool GameField::is_adjacent_to_same_type(const Position &point) const
{
	return std::ranges::any_of(Direction::instance().get_all_possible_moves().begin(), Direction::instance().get_all_possible_moves().end(), [&](const Position &direction)
	{
		const auto &pos = point + direction;

		if (is_on_map(pos))
		{
			auto *lhs = get_cell(pos).get_active_event();
			auto *rhs = get_cell(point).get_active_event();

			return lhs != nullptr && lhs == rhs;
		}
		return false;
	});
}
bool GameField::can_move(EntityHandler *caller, const Position &point) const
{
	if (!can_move(point))
	{
		return false;
	}

	auto &cell = get_cell(point);

	if (caller != nullptr && cell.has_door())
	{
		auto *handler = dynamic_cast<PlayerHandler *>(caller);

		if (handler != nullptr)
		{
			cell.get_active_event()->trigger(caller);

			return dynamic_cast<const Door *>(cell.get_active_event())->is_open();
		}
	}

	return true;
}
void GameField::swap_values(GameField &&other)
{
	clear_map();

	std::swap(dimensions_, other.dimensions_);
	std::swap(start_, other.start_);
	std::swap(finish_, other.finish_);
	std::swap(map_, other.map_);

	other.map_ = nullptr;
}
void GameField::swap_values(const GameField &other)
{
	clear_map();
	map_ = allocate_map(other.dimensions_);

	dimensions_ = other.dimensions_;
	start_ = other.start_;
	finish_ = other.finish_;

	for (int32_t i = 0; i < dimensions_.x(); ++i)
	{
		for (int32_t j = 0; j < dimensions_.y(); ++j)
		{
			map_[i][j] = other.map_[i][j];
		}
	}
}

// A* search algorithm
// https://en.wikipedia.org/wiki/A*_search_algorithm
std::vector<Position> GameField::find_route(EntityHandler *caller, const Position &begin, const Position &goal) const
{
	// Define the heuristic function
	auto heuristic = [](const Position &p1, const Position &p2) -> int
	{
		return abs(p1.x() - p2.x()) + abs(p1.y() - p2.y());
	};

	std::priority_queue<std::pair<int, Position>, std::vector<std::pair<int, Position>>, std::greater<>> frontier;
	std::map<Position, Position> came_from;
	std::map<Position, int> cost_so_far;
	bool found_path = false;

	// push start point
	frontier.push(std::move(std::make_pair(0, begin)));
	cost_so_far[begin] = 0;

	// While there is still places to go
	while (!frontier.empty())
	{
		auto current = frontier.top().second;
		frontier.pop();

		// If we reached our goal we can stop
		if (current == goal)
		{
			found_path = true;
			break;
		}

		// Check all neighbours
		for (auto &dir: Direction::instance().get_all_possible_moves())
		{
			const auto &next = current + dir;

			// Check if the neighbour is in the grid and is not a wall
			if (!can_move(caller, next))
			{
				continue;
			}

			auto new_cost = cost_so_far[current] + 1;

			// If it's a new node or we found a better way to get to this node
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				auto priority = new_cost + heuristic(next, goal);
				frontier.push(std::move(std::make_pair(priority, next)));
				came_from[next] = current;
			}
		}
	}

	// Reconstruct the path
	std::vector<Position> path;

	if (found_path)
	{
		auto current = goal;
		while (current != begin)
		{
			path.push_back(current);
			current = came_from[current];
		}
		path.push_back(begin);
		std::reverse(path.begin(), path.end());
	}
	return path;
}
bool GameField::can_move(const Position &point) const
{
	return is_on_map(point) && get_cell(point).is_movable();
}
