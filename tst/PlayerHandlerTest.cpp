#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(PlayerHandlerTestSuite, TestInvalidConstructor)
{
	try
	{
		PlayerHandler handler(nullptr);

		// should not be here any way
		FAIL();
	}
	catch (const std::invalid_argument &ex)
	{
	}
}

TEST(PlayerHandlerTestSuite, TestConstructor)
{
	auto *player = new Player;
	auto *map = new GameField;
	PlayerHandler handler(player);
	handler.register_observer(map);

	EXPECT_EQ(player->get_health(), handler.get_health());
	EXPECT_EQ(player->get_armor(), handler.get_armor());
	EXPECT_EQ(player->get_defense(), handler.get_defense());
	EXPECT_EQ(player->get_points(), handler.get_points());

	delete map;
}

TEST(PlayerHandlerTestSuite, TestPlayerMove)
{
	auto *map = new GameField;
	PlayerHandler handler(new Player);
	handler.register_observer(map);

	map->build_wall({0, 1});
	EXPECT_EQ(map->get_cell({0, 1}).is_movable(), false);
	EXPECT_EQ(map->is_on_map({0, 1}), true);
	EXPECT_EQ(map->get_cell({0, 1}).is_movable(), false);
	EXPECT_EQ(map->can_move({0, 1}), false);

	handler.move_by_direction(RIGHT, 1);
	ASSERT_EQ(handler.get_position(), Position(0, 0));

	handler.move_by_direction(DOWN, 2);
	ASSERT_EQ(handler.get_position(), Position(2, 0));

	handler.move_by_direction(LEFT, 1);
	ASSERT_EQ(handler.get_position(), Position(2, 0));

	delete map;
}