#include <Entities/Player/Player.hpp>
#include "gtest/gtest.h"

TEST(PlayerTestSuite, TestDefaultConstructor)
{
	Player player;

	EXPECT_EQ(player.get_health(), 100);
	EXPECT_EQ(player.get_armor(), 0);
	EXPECT_EQ(player.get_attack(), 10);
	EXPECT_EQ(player.get_defense(), 10);
	EXPECT_EQ(player.get_points(), 0);
}

TEST(PlayerTestSuite, TestBasicConstructor)
{
	Player player(100, 15);

	EXPECT_EQ(player.get_health(), 100);
	EXPECT_EQ(player.get_armor(), 15);
	EXPECT_EQ(player.get_attack(), 10);
	EXPECT_EQ(player.get_defense(), 10);
	EXPECT_EQ(player.get_points(), 0);
}

TEST(PlayerTestSuite, TestCopyConstructor)
{
	Player player(10, 1, 1, 2, 100);
	Player player_copy(player);

	EXPECT_EQ(player.get_health(), player_copy.get_health());
	EXPECT_EQ(player.get_armor(), player_copy.get_armor());
	EXPECT_EQ(player.get_attack(), player_copy.get_attack());
	EXPECT_EQ(player.get_defense(), player_copy.get_defense());
	EXPECT_EQ(player.get_points(), player_copy.get_points());

	player_copy.set_health(0);
	EXPECT_EQ(player_copy.get_health(), 0);
	EXPECT_EQ(player.get_health(), 10);
}

TEST(PlayerTestSuite, TestMoveConstructor)
{
	Player player(std::move(Player(50)));

	EXPECT_EQ(player.get_health(), 50);
}

TEST(PlayerTestSuite, TestSetters)
{
	Player player;

	EXPECT_EQ(player.get_points(), 0);

	player.set_points(500);

	EXPECT_EQ(player.get_points(), 500);

	player.set_points(-1);

	EXPECT_EQ(player.get_points(), 0);
}

