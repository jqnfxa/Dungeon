#include "Potion.hpp"

Potion::Potion(PlayerHandler &handler) : handler_(handler)
{
}

void Potion::trigger() const
{
	handler_.set_health(handler_.get_health() + health_increase);
	handler_.set_attack(handler_.get_attack() + attack_increase);
}

bool Potion::is_temporary() const
{
	return temporary_state_;
}

Potion *Potion::copy() const
{
	return new Potion(*this);
}

bool Potion::operator==(EventInterface *event) const
{
	return dynamic_cast<Potion *>(event) != nullptr;
}