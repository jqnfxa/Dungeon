#include "Spikes.hpp"
#include "../Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cmath>

void Spikes::interaction(HandlerInterface *handler) const
{
	auto *ptr = dynamic_cast<PlayerHandler *>(handler);
	if (ptr == nullptr)
	{
		return;
	}
	if (ptr->get_armor() > 10)
	{
		ptr->set_armor(std::floor(armor_decrease_multiplier * ptr->get_armor()));
	}
	else
	{
		ptr->set_health(ptr->get_health() - no_armor_damage);
	}
}
Spikes *Spikes::copy() const
{
	return new Spikes(*this);
}
Spikes *Spikes::create() const
{
	return new Spikes();
}
