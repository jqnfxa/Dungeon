#include "PlayerHandler.hpp"

PlayerHandler::PlayerHandler(Player *player) : player_(player)
{
	if (player_ == nullptr)
	{
		throw std::invalid_argument("Nullptr passed to PlayerHandler");
	}
}
PlayerHandler::~PlayerHandler()
{
	delete player_;
}
Position PlayerHandler::get_position() const
{
	return player_->get_position();
}
int32_t PlayerHandler::get_health() const
{
	return player_->get_health();
}
int32_t PlayerHandler::get_armor() const
{
	return player_->get_armor();
}
int32_t PlayerHandler::get_attack() const
{
	return player_->get_attack();
}
int32_t PlayerHandler::get_defense() const
{
	return player_->get_defense();
}
int32_t PlayerHandler::get_points() const
{
	return player_->get_points();
}
void PlayerHandler::set_position(int32_t new_value)
{
	player_->set_position(new_value);
}
void PlayerHandler::set_health(int32_t new_value)
{
	player_->set_health(new_value);
}
void PlayerHandler::set_attack(int32_t new_value)
{
	player_->set_attack(new_value);
}
void PlayerHandler::set_defense(int32_t new_value)
{
	player_->set_defense(new_value);
}
void PlayerHandler::set_points(int32_t new_value)
{
	player_->set_points(new_value);
}
void PlayerHandler::move_by_direction(DIRECTION direction, int32_t multiplier)
{
	for (int32_t i = 0; i < multiplier; ++i)
	{
		set_position(Direction::getInstance().calculate_position(player_->get_position(), direction));
	}
}
