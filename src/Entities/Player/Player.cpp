#include "Player.hpp"

Player::Player(const Position &position, const int32_t &health, const int32_t &armor, const int32_t &attack, const int32_t &defence, const int32_t &points) : position_(position),
																																							  health_(health),
																																							  armor_(armor),
																																							  attack_(attack),
																																							  defence_(defence),
																																							  points_(points)
{
}
Player::Player(const Player &player)
{
	*this = player;
}
Player::Player(Player &&player) noexcept
{
	*this = std::move(player);
}
Player &Player::operator=(const Player &player)
{
	if (this != &player)
	{
		position_ = player.position_;
		health_ = player.health_;
		armor_ = player.armor_;
		attack_ = player.attack_;
		defence_ = player.defence_;
		points_ = player.points_;
	}

	return *this;
}
Player &Player::operator=(Player &&player) noexcept
{
	if (this != &player)
	{
		position_ = std::move(player.position_);
		health_ = std::move(player.health_);
		armor_ = std::move(player.armor_);
		attack_ = std::move(player.attack_);
		defence_ = std::move(player.defence_);
		points_ = std::move(player.points_);
	}

	return *this;
}
Position Player::get_position() const
{
	return position_;
}
int32_t Player::get_health() const
{
	return health_;
}
int32_t Player::get_armor() const
{
	return armor_;
}
int32_t Player::get_attack() const
{
	return attack_;
}
int32_t Player::get_defense() const
{
	return defence_;
}
int32_t Player::get_points() const
{
	return points_;
}
void Player::set_position(const Position &new_value)
{
	position_ = new_value;
}
void Player::set_health(const int32_t &new_value)
{
	health_ = new_value;
	adjust(health_, 100);
}
void Player::set_armor(const int32_t &new_value)
{
	armor_ = new_value;
	adjust(armor_, 100);
}
void Player::set_attack(const int32_t &new_value)
{
	attack_ = new_value;
	adjust(attack_, 50);
}
void Player::set_defense(const int32_t &new_value)
{
	defence_ = new_value;
	adjust(defence_, 50);
}
void Player::set_points(const int32_t &new_value)
{
	points_ = new_value;
	adjust(points_, 1000);
}
void Player::adjust(int32_t &value, const int32_t &limit)
{
	value = std::max(0, value);
	value = std::min(value, limit);
}
