#include "Random.hpp"
#include "Event/Factory/EventFactory.hpp"
#include <random>

DIRECTION Random::pick_direction() const
{
	auto &directions = Direction::instance().get_all_possible_moves();
	return static_cast<DIRECTION>(pick_num(static_cast<size_t>(0), directions.size() - 1));
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
		event = EventFactory::instance().create(static_cast<EVENT_TYPE>(pick_num<int16_t>(EVENT_TYPE::POTION, EVENT_TYPE::STAR)));
	}
	else if (group == NEGATIVE)
	{
		event = EventFactory::instance().create(EVENT_TYPE::SPIKES);
	}
	return event;
}