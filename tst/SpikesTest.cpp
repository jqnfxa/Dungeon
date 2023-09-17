#include <Event/Spikes.hpp>
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(TestSpikesSuite, TestSpikesInteraction)
{
	auto *player = new Player(Position(0, 0), 100, 20);
	Map map;
	MapHandler map_handler(&map);
	PlayerHandler player_handler(player, map_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	EventInterface *event = new Spikes;
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 10);

	delete event;
}