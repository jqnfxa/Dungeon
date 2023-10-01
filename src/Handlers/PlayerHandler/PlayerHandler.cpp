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
	if (map_observer_ == nullptr)
	{
		throw std::invalid_argument("MapHandler was not initialized");
	}
	for (int32_t i = 0; i < multiplier; ++i)
	{
		auto new_position = Direction::instance().calculate_position(position_, direction);

		if (map_observer_->can_move(new_position))
		{
			set_position(new_position);

			auto active_event = map_observer_->get_cell(new_position).get_active_event();
			if (active_event != nullptr)
			{
				active_event->trigger();

				if (active_event->is_temporary())
				{
					map_observer_->get_cell(new_position).remove_event();
				}
			}
		}
	}

	// TODO notify subscribers about player move
}
PlayerHandler::PlayerHandler(Player *player) : player_(player), map_observer_(nullptr)
{
	if (player_ == nullptr)
	{
		throw std::invalid_argument("Nullptr passed to PlayerHandler");
	}
}
void PlayerHandler::register_observer(MapObserver *observer)
{
	map_observer_ = observer;
}
void PlayerHandler::remove_observer(MapObserver *observer)
{
	map_observer_ = nullptr;
}
const std::vector<int64_t> &PlayerHandler::keys() const
{
	return keys_;
}
void PlayerHandler::add_key(int64_t key)
{
	keys_.push_back(key);
}

