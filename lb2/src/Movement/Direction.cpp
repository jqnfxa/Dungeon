#include "Direction.hpp"

Position Direction::calculate_position(const Position &old, DIRECTION direction)
{
	return old + possible_moves_[direction];
}