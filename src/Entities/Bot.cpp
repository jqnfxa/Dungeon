#include "Bot.hpp"

Bot::Bot() : Bot(100U, 10U, 0U)
{
}
Bot::Bot(uint32_t health, uint32_t damage, uint32_t armor) : health_(health),
															 damage_(damage),
															 armor_(armor)
{
}
bool Bot::is_alive() const
{
	return health_ != 0U;
}
uint32_t Bot::get_health() const
{
	return health_;
}
uint32_t Bot::get_armor() const
{
	return armor_;
}
uint32_t Bot::get_damage() const
{
	return damage_;
}
void Bot::set_health(uint32_t health)
{
	health_ = health;
}
void Bot::set_armor(uint32_t armor)
{
	armor_ = armor;
}
void Bot::set_damage(uint32_t damage)
{
	damage_ = damage;
}
uint32_t Bot::get_row() const
{
	return row_;
}
void Bot::set_row(uint32_t row)
{
	row_ = row;
}
uint32_t Bot::get_column() const
{
	return column_;
}
void Bot::set_column(uint32_t column)
{
	column_ = column;
}

