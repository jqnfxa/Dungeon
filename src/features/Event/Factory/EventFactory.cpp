#include "EventFactory.hpp"
#include "../PositiveEvents/Potion.hpp"
#include "../PositiveEvents/ShieldKit.hpp"
#include "../PositiveEvents/Star.hpp"
#include "../NegativeEvents/Spikes.hpp"
#include "../MovementEvents/RandomMine.hpp"
#include "../MovementEvents/Door.hpp"

EventFactory::EventFactory()
{
	clear_events();

	events[RANDOM_MINE] = new RandomMine;
	events[SPIKES] = new Spikes;
	events[POTION] = new Potion;
	events[SHIELD_KIT] = new ShieldKit;
	events[STAR] = new Star;
	events[KEY] = new Key;
	events[DOOR] = new Door(*dynamic_cast<Key *>(events[KEY]));
}

EventFactory::~EventFactory()
{
	clear_events();
}

EventInterface *EventFactory::create(EVENT_TYPE type)
{
	EventInterface *event = nullptr;

	if (events.find(type) != events.end())
	{
		event = events[type]->copy();
	}
	return event;
}

void EventFactory::clear_events()
{
	for (auto &[key, value] : events)
	{
		delete value;
	}
	events.clear();
}
