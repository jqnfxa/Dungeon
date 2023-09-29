#include "RandomMine.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
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
	auto direction = Random::instance().pick_direction();
	auto power = Random::instance().pick_num(power_lower_bound_, power_upper_bound_);

	ptr->move_by_direction(direction, power);
}
RandomMine *RandomMine::copy() const
{
	return new RandomMine(*this);
}
bool RandomMine::is_temporary() const
{
	return false;
}
bool RandomMine::operator==(EventInterface *event) const
{
	return dynamic_cast<RandomMine *>(event) != nullptr;
}
