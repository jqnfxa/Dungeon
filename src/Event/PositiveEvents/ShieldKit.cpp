#include "ShieldKit.hpp"

ShieldKit::ShieldKit(PlayerHandler &handler) : handler_(handler)
{
}

void ShieldKit::trigger() const
{
	handler_.set_armor(handler_.get_armor() + shield_value);
}

bool ShieldKit::is_temporary() const
{
	return temporary_state_;
}

ShieldKit *ShieldKit::copy() const
{
	return new ShieldKit(*this);
}

bool ShieldKit::operator==(EventInterface *event) const
{
	return dynamic_cast<ShieldKit *>(event) != nullptr;
}