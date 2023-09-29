#include "Event/NegativeEvents/Spikes.hpp"
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"
#include "Event/Factory/EventFactory.hpp"

TEST(TestSpikesSuite, TestSpikesInteraction)
{
	MapHandler map_handler(new GameField);
	PlayerHandler player_handler(new Player(100, 20), &map_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	EventInterface *event = EventFactory::instance().create(EVENT_TYPE::SPIKES);
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 10);

	delete event;
}