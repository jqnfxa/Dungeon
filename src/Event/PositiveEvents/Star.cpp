#include "Star.hpp"

Star::Star(PlayerHandler &handler) : handler_(handler)
{
}

void Star::trigger() const
{
	handler_.set_points(handler_.get_points() + xp_amount);
}

bool Star::is_temporary() const
{
	return true;
}

Star *Star::copy() const
{
	return new Star(*this);
}

bool Star::operator==(EventInterface *event) const
{
	return dynamic_cast<Star *>(event) != nullptr;
}