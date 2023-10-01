#include "ShieldKit.hpp"

void ShieldKit::trigger(EntityHandler *handler) const
{
	auto *handler_ = dynamic_cast<PlayerHandler *>(handler);

	if (handler_ == nullptr)
	{
		return;
	}

	handler_->set_armor(handler_->get_armor() + shield_value);
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