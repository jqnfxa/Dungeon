#include "Door.hpp"

Door::Door(Key &key) : hash_required_(key.hash())
{
}

bool Door::is_open() const
{
	return is_open_;
}

void Door::trigger(EntityHandler *handler) const
{
	auto *handler_ = dynamic_cast<PlayerHandler *>(handler);

	if (handler_ == nullptr)
	{
		return;
	}

	if (!is_open())
	{
		bool has_needle_key = false;

		for (const auto &key: handler_->keys())
		{
			if (key == hash_required_)
			{
				has_needle_key = true;
				break;
			}
		}

		if (has_needle_key)
		{
			is_open_ = true;
		}
	}
}

bool Door::is_temporary() const
{
	return temporary_state_;
}

Door *Door::copy() const
{
	return new Door(*this);
}

bool Door::operator==(EventInterface *event) const
{
	return dynamic_cast<Door *>(event) != nullptr;
}