#include "Random.hpp"
#include "Event/Factory/EventFactory.hpp"
#include <random>

DIRECTION Random::pick_direction() const
{
	auto &directions = Direction::instance().get_all_possible_moves();
	return static_cast<DIRECTION>(pick_num(0, directions.size() - 1));
}
int32_t Random::pick_num(int32_t from, int32_t to) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int32_t> distribution(from, to);

	return distribution(gen);
}
EventInterface *Random::pick_event(EVENT_GROUP group)
{
	EventInterface *event = nullptr;
	if (group == NEUTRAL)
	{
		event = EventFactory::instance().create(EVENT_TYPE::RANDOM_MINE);
	}
	else if (group == POSITIVE)
	{
		event = EventFactory::instance().create(static_cast<EVENT_TYPE>(pick_num(EVENT_TYPE::POTION, EVENT_TYPE::STAR)));
	}
	else if (group == NEGATIVE)
	{
		event = EventFactory::instance().create(EVENT_TYPE::SPIKES);
	}
	return event;
}