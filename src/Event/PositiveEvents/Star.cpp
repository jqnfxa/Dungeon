#include "Star.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"

void Star::interaction(HandlerInterface *handler) const
{
	auto *ptr = dynamic_cast<PlayerHandler *>(handler);
	if (ptr == nullptr)
	{
		return;
	}
	ptr->set_points(ptr->get_points() + xp_amount);
}
Star *Star::copy() const
{
	return new Star(*this);
}
bool Star::is_temporary() const
{
	return true;
}
bool Star::operator==(EventInterface *event) const
{
	return dynamic_cast<Star *>(event) != nullptr;
}
