#include "WorldManager.hpp"

// TODO call Map constructor with new dimensions
WorldManager::WorldManager(uint32_t dim_x, uint32_t dim_y)
{
}
// TODO pass Map class to do bound check
void WorldManager::move_player(const Direction &direction)
{
	/*
	 * TODO bound check
	 */
	int32_t new_row = static_cast<int32_t>(player_.get_row()) + moves[direction][0U];
	int32_t new_column = static_cast<int32_t>(player_.get_column()) + moves[direction][1U];

	if (new_row < 0 || new_column < 0)
	{
		return;
	}

	player_.set_row(static_cast<uint32_t>(new_row));
	player_.set_column(static_cast<uint32_t>(new_column));
}
