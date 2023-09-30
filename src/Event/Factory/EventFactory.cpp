#include "EventFactory.hpp"
#include "../PositiveEvents/Potion.hpp"
#include "../PositiveEvents/ShieldKit.hpp"
#include "../PositiveEvents/Star.hpp"
#include "../NegativeEvents/Spikes.hpp"
#include "../MovementEvents/RandomMine.hpp"

EventFactory::EventFactory() : handler_(nullptr)
{
}

void EventFactory::reset_player_reference(PlayerHandler *handler)
{
	handler_ = handler;
}

EventInterface *EventFactory::create(EVENT_TYPE type)
{
	EventInterface *event = nullptr;

	if (handler_ != nullptr)
	{
		switch (type)
		{
			case RANDOM_MINE: event = new RandomMine(*handler_);
				break;
			case SPIKES: event = new Spikes(*handler_);
				break;
			case POTION: event = new Potion(*handler_);
				break;
			case SHIELD_KIT: event = new ShieldKit(*handler_);
				break;
			case STAR: event = new Star(*handler_);
				break;
			default: event = nullptr;
				break;
		}
	}
	return event;
}