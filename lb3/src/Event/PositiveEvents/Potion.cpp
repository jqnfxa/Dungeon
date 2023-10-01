#include "Potion.hpp"

void Potion::trigger(EntityHandler *handler) const
{
	auto *handler_ = dynamic_cast<PlayerHandler *>(handler);

	if (handler_ == nullptr)
	{
		return;
	}

	handler_->set_health(handler_->get_health() + health_increase);
	handler_->set_attack(handler_->get_attack() + attack_increase);
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