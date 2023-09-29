#include "MapHandler.hpp"

MapHandler::MapHandler(GameField *map) : map_(map)
{
	if (map_ == nullptr)
	{
		throw std::invalid_argument("Nullptr passed to MapHandler");
	}
}
Cell &MapHandler::get_cell(const Position &point) const
{
	return map_->get_cell(point);
}
void MapHandler::set_cell(const Position &point, const Cell &new_cell) const
{
	map_->set_cell(point, new_cell);
}
void MapHandler::set_cell(const Position &point, Cell &&new_cell) const
{
	map_->set_cell(point, std::move(new_cell));
}
bool MapHandler::can_move(const Position &point) const
{
	// TODO check for other npc?
	return map_->can_move(point);
}
MapHandler::~MapHandler()
{
	delete map_;
}

