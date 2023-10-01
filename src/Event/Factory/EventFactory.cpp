#include "EventFactory.hpp"
#include "../PositiveEvents/Potion.hpp"
#include "../PositiveEvents/ShieldKit.hpp"
#include "../PositiveEvents/Star.hpp"
#include "../NegativeEvents/Spikes.hpp"
#include "../MovementEvents/RandomMine.hpp"
#include "../MovementEvents/Key.hpp"
#include "../MovementEvents/Door.hpp"

EventFactory::EventFactory() : handler_(nullptr)
{
}

EventFactory::~EventFactory()
{
	clear_events();
}

void EventFactory::reset_player_reference(PlayerHandler *handler)
{
	handler_ = handler;

	clear_events();

	events[RANDOM_MINE] = new RandomMine(*handler_);
	events[SPIKES] = new Spikes(*handler_);
	events[POTION] = new Potion(*handler_);
	events[SHIELD_KIT] = new ShieldKit(*handler_);
	events[STAR] = new Star(*handler_);
	events[KEY] = new Key(*handler_);
	events[DOOR] = new Door(*handler_, *dynamic_cast<Key *>(events[KEY]));
}

EventInterface *EventFactory::create(EVENT_TYPE type)
{
	EventInterface *event = nullptr;

	if (handler_ != nullptr && events.find(type) != events.end())
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
