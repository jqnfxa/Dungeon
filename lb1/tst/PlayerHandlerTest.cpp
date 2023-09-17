#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(PlayerHandlerTestSuite, TestInvalidConstructor)
{
	try
	{
		Map map;
		MapHandler map_handler(&map);
		PlayerHandler handler(nullptr, map_handler);

		// should not be here any way
		FAIL();
	}
	catch (const std::invalid_argument &ex)
	{
	}
}

TEST(PlayerHandlerTestSuite, TestConstructor)
{
	Player *player = new Player;
	Map map;
	MapHandler map_handler(&map);
	PlayerHandler handler(player, map_handler);

	EXPECT_EQ(player->get_position(), handler.get_position());
	EXPECT_EQ(player->get_health(), handler.get_health());
	EXPECT_EQ(player->get_armor(), handler.get_armor());
	EXPECT_EQ(player->get_defense(), handler.get_defense());
	EXPECT_EQ(player->get_points(), handler.get_points());
}

TEST(PlayerHandlerTestSuite, TestPlayerMove)
{
	Player *player = new Player;
	Map *map = new Map;
	MapHandler map_handler(map);
	PlayerHandler handler(player, map_handler);

	map->build_wall({0, 1});
	handler.move_by_direction(right, 1);
	ASSERT_EQ(handler.get_position(), Position(0, 0));

	handler.move_by_direction(down, 2);
	ASSERT_EQ(handler.get_position(), Position(2, 0));

	delete map;
}