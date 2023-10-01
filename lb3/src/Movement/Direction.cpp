#include "Direction.hpp"

Position Direction::calculate_position(const Position &old, DIRECTION direction)
{
	return old + possible_moves_[direction];
}
Direction::Direction()
{
	std::copy(possible_moves_sharable.begin(), possible_moves_sharable.end(), std::back_inserter(possible_moves_));
}
const std::vector<Position> &Direction::get_all_possible_moves() const
{
	return possible_moves_sharable;
}
