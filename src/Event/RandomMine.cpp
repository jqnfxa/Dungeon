#include "RandomMine.hpp"
#include "../Handlers/PlayerHandler/PlayerHandler.hpp"
#include "Random/Random.hpp"
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
	return Random::get_instance().pick_direction();
}
int32_t RandomMine::pick_power() const
{
	return Random::get_instance().pick_num(1, 5);
}

RandomMine *RandomMine::copy() const
{
	return new RandomMine(*this);
}
RandomMine *RandomMine::create() const
{
	return new RandomMine;
}