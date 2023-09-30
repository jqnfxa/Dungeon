#include "RandomMine.hpp"
#include "Random/Random.hpp"

RandomMine::RandomMine(PlayerHandler &handler) : handler_(handler)
{
}

void RandomMine::trigger() const
{
	auto direction = Random::instance().pick_direction();
	auto power = Random::instance().pick_num(power_lower_bound_, power_upper_bound_);

	handler_.move_by_direction(direction, power);
}

bool RandomMine::is_temporary() const
{
	return temporary_state_;
}

RandomMine *RandomMine::copy() const
{
	return new RandomMine(*this);
}

bool RandomMine::operator==(EventInterface *event) const
{
	return dynamic_cast<RandomMine *>(event) != nullptr;
}