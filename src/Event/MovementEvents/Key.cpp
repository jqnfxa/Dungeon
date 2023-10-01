#include "Key.hpp"
#include "Random/Random.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"

Key::Key(PlayerHandler &handler) : handler_(handler), hash_(Random::instance().pick_num<int64_t>(INT32_MAX, INT64_MAX))
{
}

int64_t Key::hash() const
{
	return hash_;
}

void Key::trigger() const
{
	handler_.add_key(hash());
}

bool Key::is_temporary() const
{
	return temporary_state_;
}
Key *Key::copy() const
{
	return new Key(*this);
}

bool Key::operator==(EventInterface *event) const
{
	return dynamic_cast<Key *>(event) != nullptr;
}

