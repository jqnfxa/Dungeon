#include <algorithm>
#include "Player.hpp"

Player::Player() : Player(100U, 0U, 10U, 0U)
{
}
Player::Player(uint32_t health, uint32_t points, uint32_t damage, uint32_t armor) : points_(points), Bot(health,
																										 damage,
																										 armor)
{
}
uint32_t Player::get_points() const
{
	return points_;
}
void Player::set_points(uint32_t points)
{
	points_ = points;
}
