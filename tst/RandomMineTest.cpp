#include <Event/RandomMine.hpp>
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(TestRandomMineSuite, TestMineInteraction)
{
	auto *map = new Map(100, 100);
	map->build_wall({51, 50});
	map->build_wall({49, 50});
	map->build_wall({50, 49});

	MapHandler map_handler(map);
	PlayerHandler player_handler(new Player(100, 20), &map_handler);
	player_handler.set_position({50, 50});

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	EventInterface *event = new RandomMine;
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_position(), Position(50, player_handler.get_position().get_y()));
	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	delete event;
}