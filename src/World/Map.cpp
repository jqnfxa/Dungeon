#include "Map.hpp"
#include "Event/Spikes.hpp"
#include "Event/Potion.hpp"
#include "Event/RandomMine.hpp"
#include <ostream>

Map::Map(const Dimension &dimensions) : dimensions_(dimensions), start_(-1, -1), finish_(-1, -1), map_(nullptr)
{
	if (dimensions_.get_x() < MAP_DIMENSION_LOWER_BOUND || dimensions_.get_y() < MAP_DIMENSION_LOWER_BOUND
		|| dimensions_.get_x() > MAP_DIMENSION_UPPER_BOUND || dimensions_.get_y() > MAP_DIMENSION_UPPER_BOUND)
	{
		throw std::logic_error("Unexpected dimensions for map (too small or too big)");
	}
	map_ = allocate_map(dimensions_);
}
Map::Map(int32_t dim_x, int32_t dim_y) : Map(Vector2<int32_t>{dim_x, dim_y})
{
}
Map::~Map()
{
	clear_map();
}
Map::Map() : Map(MAP_DIMENSION_LOWER_BOUND, MAP_DIMENSION_LOWER_BOUND)
{
}
Map::Map(const Map &other) : Map()
{
	*this = other;
}
Map::Map(Map &&other) noexcept: Map()
{
	*this = std::move(other);
}
Map &Map::operator=(const Map &other)
{
	if (&other != this)
	{
		clear_map();
		map_ = allocate_map(other.dimensions_);

		dimensions_ = other.dimensions_;
		start_ = other.start_;
		finish_ = other.finish_;

		for (int32_t i = 0; i < dimensions_.get_x(); ++i)
		{
			for (int32_t j = 0; j < dimensions_.get_y(); ++j)
			{
				this->map_[i][j] = other.map_[i][j];
			}
		}
	}
	return *this;
}
Map &Map::operator=(Map &&other) noexcept
{
	if (&other != this)
	{
		clear_map();
		dimensions_ = std::move(other.dimensions_);
		start_ = std::move(other.start_);
		finish_ = std::move(other.finish_);
		map_ = std::move(other.map_);

		// manually zeroing ptr because we moved it
		other.map_ = nullptr;
	}
	return *this;
}
void Map::clear_map()
{
	if (map_ == nullptr)
	{
		return;
	}

	for (int32_t i = 0; i < dimensions_.get_x(); ++i)
	{
		for (int32_t j = 0; j < dimensions_.get_y(); ++j)
		{
			map_[i][j].remove_event();
		}
		delete[] map_[i];
	}
	delete[] map_;
	map_ = nullptr;
}
Cell **Map::allocate_map(const Dimension &dimensions)
{
	auto map = new Cell *[dimensions.get_x()];

	for (int32_t i = 0; i < dimensions.get_x(); ++i)
	{
		map[i] = new Cell[dimensions.get_y()];

		for (int32_t j = 0; j < dimensions.get_y(); ++j)
		{
			map[i][j] = Cell();
		}
	}
	return map;
}
Cell &Map::get_cell(const Position &point) const
{
	if (!is_on_map(point))
	{
		throw std::out_of_range("Point is out of map");
	}
	return map_[point.get_x()][point.get_y()];
}
void Map::set_cell(const Position &point, Cell &&new_cell)
{
	if (!is_on_map(point))
	{
		return;
	}
	// TODO release resources of old cell ?
	map_[point.get_x()][point.get_y()] = std::move(new_cell);
}
void Map::set_cell(const Position &point, const Cell &new_cell)
{
	if (!is_on_map(point))
	{
		return;
	}
	map_[point.get_x()][point.get_y()] = new_cell;
}
const Dimension &Map::get_dimensions() const
{
	return dimensions_;
}
void Map::reset_start(const Position &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		if (start_ != Vector2<int32_t>(-1, -1))
		{
			map_[start_.get_x()][start_.get_y()].set_type(Cell::Type::MOVABLE);
		}
		start_ = point;
		map_[start_.get_x()][start_.get_y()].set_type(Cell::Type::ENTRANCE);
	}
}
void Map::reset_finish(const Vector2<int32_t> &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		if (finish_ != Vector2<int32_t>(-1, -1))
		{
			map_[finish_.get_x()][finish_.get_y()].set_type(Cell::Type::MOVABLE);
		}
		finish_ = point;
		map_[finish_.get_x()][finish_.get_y()].set_type(Cell::Type::EXIT);
	}
}
void Map::build_wall(const Position &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		map_[point.get_x()][point.get_y()].set_type(Cell::Type::WALL);
	}
}
void Map::destroy_wall(const Position &point)
{
	if (is_on_map(point) && !get_cell(point).is_movable())
	{
		map_[point.get_x()][point.get_y()].set_type(Cell::Type::MOVABLE);
	}
}
bool Map::is_on_map(const Position &point) const
{
	return point.get_x() >= 0 && point.get_y() >= 0 && point.get_x() < dimensions_.get_x()
		   && point.get_y() < dimensions_.get_y();
}
const Position &Map::get_start_point() const
{
	return start_;
}
const Position &Map::get_finish_point() const
{
	return finish_;
}
std::ostream &Map::print(std::ostream &out) const
{
	for (int i = 0; i < dimensions_.get_x(); i++)
	{
		for (int j = 0; j < dimensions_.get_y(); j++)
		{
			auto &cell = get_cell({i, j});
			if (cell.is_entrance())
			{
				out << '0';
			}
			else if (cell.is_exit())
			{
				out << '1';
			}
			else if (!cell.is_movable())
			{
				out << '*';
			}
			else
			{
				if (cell.get_active_event() == nullptr)
				{
					out << ' ';
				}
				else if (const auto *p = dynamic_cast<const Spikes *>(cell.get_active_event()); p != nullptr)
				{
					out << '#';
				}
				else if (const auto *k = dynamic_cast<const Potion *>(cell.get_active_event()); k != nullptr)
				{
					out << '+';
				}
				else if (const auto *d = dynamic_cast<const RandomMine *>(cell.get_active_event()); d != nullptr)
				{
					out << '?';
				}
			}
		}
		out << '\n';
	}
	return out << std::endl;
}
bool Map::is_adjacent_to_movable(const Position &point) const
{
	for (int i = 1; i <= 4; ++i)
	{
		Position neighbor(Direction::getInstance().calculate_position(point, static_cast<DIRECTION>(i)));

		if (is_on_map(neighbor) && get_cell(neighbor).is_movable())
		{
			return true;
		}
	}
	return false;
}
