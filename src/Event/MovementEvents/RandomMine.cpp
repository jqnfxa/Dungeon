#include "RandomMine.hpp"
#include "Random/Random.hpp"

void RandomMine::trigger(EntityHandler *handler) const
{
	auto *handler_ = dynamic_cast<PlayerHandler *>(handler);

	if (handler_ == nullptr)
	{
		return;
	}

	auto direction = Random::instance().pick_direction();
	auto power = Random::instance().pick_num(power_lower_bound_, power_upper_bound_);

	handler_->move_by_direction(direction, power);
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