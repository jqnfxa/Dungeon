#include <algorithm>
#include "Map.hpp"

Map::Map(const Dimension &dimensions) : dimensions_(dimensions), start_(-1, -1), finish_(-1, -1), map_(nullptr)
{
	if (dimensions_.get_x() < 10 || dimensions_.get_y() < 10 || dimensions_.get_x() > 1000
		|| dimensions_.get_y() > 1000)
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
Map::Map() : Map(10, 10)
{
}
Map::Map(const Map &other) : map_(nullptr)
{
	*this = other;
}
Map::Map(Map &&other) noexcept
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

		for (uint32_t i = 0U; i < dimensions_.get_x(); ++i)
		{
			for (uint32_t j = 0U; j < dimensions_.get_y(); ++j)
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

	for (uint32_t i = 0U; i < dimensions_.get_x(); ++i)
	{
		delete[] map_[i];
	}
	delete[] map_;
}
Cell **Map::allocate_map(const Dimension &dimensions)
{
	auto map = new Cell *[dimensions.get_x()];

	for (uint32_t i = 0U; i < dimensions.get_x(); ++i)
	{
		map[i] = new Cell[dimensions.get_y()];
	}
	return map;
}
const Cell &Map::get_cell(const Position &point) const
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
Dimension Map::get_dimensions() const
{
	return dimensions_;
}
void Map::reset_start(const Position &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		if (start_ != Vector2<int32_t>(-1, -1))
		{
			map_[start_.get_x()][start_.get_y()].set_type(Cell::Type::movable);
		}
		start_ = point;
		map_[start_.get_x()][start_.get_y()].set_type(Cell::Type::start);
	}
}
void Map::reset_finish(const Vector2<int32_t> &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		if (finish_ != Vector2<int32_t>(-1, -1))
		{
			map_[finish_.get_x()][finish_.get_y()].set_type(Cell::Type::movable);
		}
		finish_ = point;
		map_[finish_.get_x()][finish_.get_y()].set_type(Cell::Type::finish);
	}
}
void Map::build_wall(const Position &point)
{
	if (is_on_map(point) && get_cell(point).is_movable())
	{
		map_[point.get_x()][point.get_y()].set_type(Cell::Type::wall);
	}
}
void Map::destroy_wall(const Position &point)
{
	if (is_on_map(point) && !get_cell(point).is_movable())
	{
		map_[point.get_x()][point.get_y()].set_type(Cell::Type::movable);
	}
}
bool Map::is_on_map(const Position &point) const
{
	return point.get_x() >= 0 && point.get_y() >= 0 && point.get_x() < dimensions_.get_x()
		   && point.get_y() < dimensions_.get_y();
}
Position Map::get_start_point() const
{
	return start_;
}
Position Map::get_finish_point() const
{
	return finish_;
}
