#include "Random.hpp"
#include "Event/MovementEvents/RandomMine.hpp"
#include "Event/PositiveEvents/Potion.hpp"
#include "Event/PositiveEvents/ShieldKit.hpp"
#include "Event/PositiveEvents/Star.hpp"
#include "Event/NegativeEvents/Spikes.hpp"
#include <random>

Random &Random::get_instance()
{
	static Random random;
	return random;
}
DIRECTION Random::pick_direction() const
{
	return static_cast<DIRECTION>(pick_num(UP, LEFT));
}
int32_t Random::pick_num(int32_t from, int32_t to) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int32_t> distribution(from, to);

	return distribution(gen);
}
EventInterface *Random::pick_event(EVENT_TYPE type)
{
	EventInterface *event = nullptr;
	if (type == NEUTRAL)
	{
		event = new RandomMine;
	}
	else if (type == POSITIVE)
	{
		auto pick = pick_num(0, 2);

		switch (pick)
		{
			case 0:
				event = new Potion;
				break;
			case 1:
				event = new ShieldKit;
				break;
			case 2:
				event = new Star;
		}
	}
	else if (type == NEGATIVE)
	{
		event = new Spikes;
	}
	return event;
}
