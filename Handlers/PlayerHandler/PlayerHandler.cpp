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
void PlayerHandler::set_position(const Position &new_value)
{
	player_->set_position(new_value);
}
void PlayerHandler::set_health(const int32_t &new_value)
{
	player_->set_health(new_value);
}
void PlayerHandler::set_attack(const int32_t &new_value)
{
	player_->set_attack(new_value);
}
void PlayerHandler::set_defense(const int32_t &new_value)
{
	player_->set_defense(new_value);
}
void PlayerHandler::set_points(const int32_t &new_value)
{
	player_->set_points(new_value);
}
void PlayerHandler::move_by_direction(const DIRECTION &direction, const int32_t &multiplier)
{
	for (int32_t i = 0; i < multiplier; ++i)
	{
		auto new_position = Direction::getInstance().calculate_position(player_->get_position(), direction);

		if (map_->is_on_map(new_position) && map_->get_cell(new_position).is_movable())
		{
			set_position(new_position);
		}
	}

	// TODO notify subscribers about player move
}
void PlayerHandler::set_map(Map *map)
{
	map_ = map;
}
Map *PlayerHandler::release_map()
{
	auto *ret = map_;
	map_ = nullptr;
	return ret;
}
