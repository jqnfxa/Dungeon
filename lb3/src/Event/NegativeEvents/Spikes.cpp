#include "Spikes.hpp"
#include <cmath>

void Spikes::trigger(EntityHandler *handler) const
{
	auto *handler_ = dynamic_cast<PlayerHandler *>(handler);

	if (handler_ == nullptr)
	{
		return;
	}

	if (handler_->get_armor() > critical_armor_value)
	{
		handler_->set_armor(std::floor(armor_decrease_multiplier * handler_->get_armor()));
	}
	else
	{
		handler_->set_health(handler_->get_health() - no_armor_damage);
	}
}

bool Spikes::is_temporary() const
{
	return temporary_state_;
}

Spikes *Spikes::copy() const
{
	return new Spikes(*this);
}

bool Spikes::operator==(EventInterface *event) const
{
	return dynamic_cast<Spikes *>(event) != nullptr;
}
