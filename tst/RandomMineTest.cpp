#include <Event/RandomMine.hpp>
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(TestRandomMineSuite, TestMineInteraction)
{
	auto *player = new Player(Position(50, 50), 100, 20);
	auto *map = new Map(100, 100);
	map->build_wall({51, 50});
	map->build_wall({49, 50});
	map->build_wall({50, 49});

	MapHandler map_handler(map);
	PlayerHandler player_handler(player, map_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	EventInterface *event = new RandomMine;
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_position(), Position(50, player_handler.get_position().get_y()));
	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_armor(), 20);

	delete event;
	delete map;
}