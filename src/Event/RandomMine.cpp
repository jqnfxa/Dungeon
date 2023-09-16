#include "RandomMine.hpp"
#include "../Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cmath>
#include <random>

void RandomMine::interaction(HandlerInterface *handler) const
{
	auto *ptr = dynamic_cast<PlayerHandler *>(handler);
	if (ptr == nullptr)
	{
		return;
	}
	auto direction = pick_direction();
	auto power = pick_power();

	ptr->move_by_direction(direction, power);
}
DIRECTION RandomMine::pick_direction() const
{
	// TODO don't forget to change picking if only 4 moves will possible
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int16_t> dis(1, 8);

	int16_t dir = 0;
	while (dir == 0 || dir % 2)
	{
		dir = dis(gen);
	}

	return static_cast<DIRECTION>(dir);
}
int32_t RandomMine::pick_power() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int16_t> dis(1, 5);

	return dis(gen);
}

RandomMine *RandomMine::copy() const
{
	return new RandomMine(*this);
}
RandomMine *RandomMine::create() const
{
	return new RandomMine;
}