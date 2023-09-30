#include "GameField.hpp"
#include "Movement/Direction.hpp"
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
bool GameField::can_move(const Position &point) const
{
	return is_on_map(point) && get_cell(point).is_movable();
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
std::vector<Position> GameField::find_route(const Position &begin, const Position &end) const
{
	int m = dimensions().x();
	int n = dimensions().y();
	std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
	std::map<Position, Position> prev;
	std::queue<Position> q;

	visited[begin.x()][begin.y()] = true;
	q.push(begin);

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

			if (can_move(new_pos) && !visited[new_pos.x()][new_pos.y()])
			{
				q.push(new_pos);
				visited[new_pos.x()][new_pos.y()] = true;
				prev[new_pos] = current;
			}
		}

	}

	std::vector<Position> path;

	for (Position it = end; it != begin; it = prev[it])
	{
		path.push_back(it);
	}
	path.push_back(begin);
	std::reverse(path.begin(), path.end());

	return path;
}
