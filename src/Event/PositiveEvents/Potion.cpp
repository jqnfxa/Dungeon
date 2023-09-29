#include "Potion.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"

void Potion::interaction(HandlerInterface *handler) const
{
	auto *ptr = dynamic_cast<PlayerHandler *>(handler);
	if (ptr == nullptr)
	{
		return;
	}

	ptr->set_health(ptr->get_health() + health_increase);
	ptr->set_attack(ptr->get_attack() + attack_increase);
}
Potion *Potion::copy() const
{
	return new Potion(*this);
}
bool Potion::is_temporary() const
{
	return true;
}
bool Potion::operator==(EventInterface *event) const
{
	return dynamic_cast<Potion *>(event) != nullptr;
}
