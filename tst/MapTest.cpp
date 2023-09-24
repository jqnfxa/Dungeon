#include <World/Map.hpp>
#include "gtest/gtest.h"
#include "Event/Spikes.hpp"
#include "Entities/Player/Player.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"

TEST(MapTestSuite, TestMapDefaultContructor)
{
	Map map;

	EXPECT_EQ(map.get_dimensions(), Dimension(10, 10));
	EXPECT_EQ(map.get_start_point(), Position(-1, -1));
	EXPECT_EQ(map.get_finish_point(), Position(-1, -1));
}

TEST(MapTestSuite, TestMapContructor)
{
	Map map(11, 11);

	EXPECT_EQ(map.get_dimensions(), Dimension(11, 11));
	EXPECT_EQ(map.get_start_point(), Position(-1, -1));
	EXPECT_EQ(map.get_finish_point(), Position(-1, -1));
}

TEST(MapTestSuite, TestMapCopyContructor)
{
	Map map(11, 11);

	{
		Map copy = map;

		EXPECT_EQ(copy.get_dimensions(), Dimension(11, 11));
		EXPECT_EQ(copy.get_start_point(), Position(-1, -1));
		EXPECT_EQ(copy.get_finish_point(), Position(-1, -1));

		copy.reset_finish({1, 1});
		EXPECT_EQ(copy.get_finish_point(), Position(1, 1));
		EXPECT_EQ(map.get_start_point(), Position(-1, -1));
	}
}

TEST(MapTestSuite, TestMapMoveContructor)
{
	Map map(11, 11);
	Map copy = std::move(map);

	EXPECT_EQ(copy.get_dimensions(), Dimension(11, 11));
	EXPECT_EQ(copy.get_start_point(), Position(-1, -1));
	EXPECT_EQ(copy.get_finish_point(), Position(-1, -1));
}

TEST(MapTestSuite, TestMapCellInteraction)
{
	Map map(11, 11);

	EXPECT_EQ(map.get_cell({1, 1}), Cell(Cell::Type::MOVABLE));

	map.reset_start({1, 1});

	EXPECT_EQ(map.get_cell({1, 1}), Cell(Cell::Type::ENTRANCE));

	map.build_wall({5, 5});

	EXPECT_EQ(map.get_cell({5, 5}), Cell(Cell::Type::WALL));
	EXPECT_EQ(map.get_cell({5, 5}).is_movable(), false);

	map.destroy_wall({5, 5});

	EXPECT_EQ(map.get_cell({5, 5}), Cell(Cell::Type::MOVABLE));
	EXPECT_EQ(map.get_cell({5, 5}).is_movable(), true);

	map.reset_finish({12, 12});

	EXPECT_EQ(map.get_finish_point(), Position(-1, -1));

	map.reset_finish({10, 10});

	EXPECT_EQ(map.get_finish_point(), Position(10, 10));
	EXPECT_EQ(map.get_start_point(), Position(1, 1));
}

TEST(MapTestSuite, TestIsOnMap)
{
	Map map(11, 11);

	EXPECT_EQ(map.is_on_map({10, 10}), true);
	EXPECT_EQ(map.is_on_map({0, -1}), false);
	EXPECT_EQ(map.is_on_map({11, 1}), false);
	EXPECT_EQ(map.is_on_map({11, 11}), false);
}

TEST(MapTestSuite, TestMapCellEvents)
{
	MapHandler map_handler(new Map(11, 11));
	PlayerHandler handler(new Player, &map_handler);
	handler.set_position({4, 4});

	map_handler.get_cell({5, 5}).add_event(new Spikes);

	EXPECT_EQ(handler.get_health(), 100);

	handler.move_by_direction(DOWN, 1);
	handler.move_by_direction(RIGHT, 1);

	EXPECT_EQ(handler.get_health(), 80);
}