#include "ShieldKit.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"

void ShieldKit::interaction(HandlerInterface *handler) const
{
	auto *ptr = dynamic_cast<PlayerHandler *>(handler);
	if (ptr == nullptr)
	{
		return;
	}

	ptr->set_defense(ptr->get_defense() + shield_value);
}
bool ShieldKit::is_temporary() const
{
	return true;
}
ShieldKit *ShieldKit::copy() const
{
	return new ShieldKit(*this);
}
bool ShieldKit::operator==(EventInterface *event) const
{
	return dynamic_cast<ShieldKit *>(event) != nullptr;
}

