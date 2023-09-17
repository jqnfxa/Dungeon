#include <Event/Potion.hpp>
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(TestPotionSuite, TestPotionInteraction)
{
	auto *player = new Player(Position(0, 0), 100, 20);
	Map map;
	MapHandler map_handler(&map);
	PlayerHandler player_handler(player, map_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_attack(), 10);

	EventInterface *event = new Potion;
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	player_handler.set_health(80);
	event->interaction(&player_handler);
	EXPECT_EQ(player_handler.get_health(), 100);

	delete event;
}