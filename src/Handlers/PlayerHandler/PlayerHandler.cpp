#include "PlayerHandler.hpp"

PlayerHandler::~PlayerHandler()
{
	delete player_;
}
const Position &PlayerHandler::get_position() const
{
	return position_;
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
	position_ = new_value;
}
void PlayerHandler::set_health(int32_t new_value)
{
	player_->set_health(new_value);
}
void PlayerHandler::set_armor(int32_t new_value)
{
	player_->set_armor(new_value);
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
		auto new_position = Direction::getInstance().calculate_position(position_, direction);

		if (map_handler_ == nullptr)
		{
			throw std::invalid_argument("MapHandler was not initialized");
		}
		// TODO delayed events
		// if map_handler_.is_on_map(new_position) && map_handler.get_cell(new_position).get_active_event().type == door
		// run it (event should move us if success)
		if (map_handler_->can_move(new_position))
		{
			set_position(new_position);

			auto active_event = map_handler_->get_cell(new_position).get_active_event();
			if (active_event != nullptr)
			{
				active_event->interaction(this);

				if (active_event->is_temporary())
				{
					map_handler_->get_cell(new_position).remove_event();
				}
			}
		}
	}

	// TODO notify subscribers about player move
}
PlayerHandler::PlayerHandler(Player *player, MapHandler *handler) : player_(player), map_handler_(handler)
{
	if (player_ == nullptr)
	{
		throw std::invalid_argument("Nullptr passed to PlayerHandler");
	}
}
MapHandler *PlayerHandler::reset_map_handler(MapHandler *handler)
{
	auto *old = map_handler_;
	map_handler_ = handler;
	return old;
}
