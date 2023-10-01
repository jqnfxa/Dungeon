#include <World/GameField.hpp>
#include "gtest/gtest.h"
#include "Entities/Player/Player.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "Event/Factory/EventFactory.hpp"

TEST(GameFieldSuite, TestMapDefaultContructor)
{
	GameField map;

	EXPECT_EQ(map.dimensions(), Dimension(10, 10));
	EXPECT_EQ(map.start_point(), Position(-1, -1));
	EXPECT_EQ(map.exit_point(), Position(-1, -1));
}

TEST(GameFieldSuite, TestMapContructor)
{
	GameField map(11, 11);

	EXPECT_EQ(map.dimensions(), Dimension(11, 11));
	EXPECT_EQ(map.start_point(), Position(-1, -1));
	EXPECT_EQ(map.exit_point(), Position(-1, -1));
}

TEST(GameFieldSuite, TestMapCopyContructor)
{
	GameField map(11, 11);

	{
		GameField copy = map;

		EXPECT_EQ(copy.dimensions(), Dimension(11, 11));
		EXPECT_EQ(copy.start_point(), Position(-1, -1));
		EXPECT_EQ(copy.exit_point(), Position(-1, -1));

		copy.reset_finish({1, 1});
		EXPECT_EQ(copy.exit_point(), Position(1, 1));
		EXPECT_EQ(map.start_point(), Position(-1, -1));
	}
}

TEST(GameFieldSuite, TestMapMoveContructor)
{
	GameField map(11, 11);
	GameField copy = std::move(map);

	EXPECT_EQ(copy.dimensions(), Dimension(11, 11));
	EXPECT_EQ(copy.start_point(), Position(-1, -1));
	EXPECT_EQ(copy.exit_point(), Position(-1, -1));
}

TEST(GameFieldSuite, TestMapCellInteraction)
{
	GameField map(11, 11);

	EXPECT_EQ(map.get_cell({1, 1}), Cell(Cell::TYPE::MOVABLE));

	map.reset_start({1, 1});

	EXPECT_EQ(map.get_cell({1, 1}), Cell(Cell::TYPE::ENTRANCE));

	map.build_wall({5, 5});

	EXPECT_EQ(map.get_cell({5, 5}), Cell(Cell::TYPE::WALL));
	EXPECT_EQ(map.get_cell({5, 5}).is_movable(), false);

	map.destroy_wall({5, 5});

	EXPECT_EQ(map.get_cell({5, 5}), Cell(Cell::TYPE::MOVABLE));
	EXPECT_EQ(map.get_cell({5, 5}).is_movable(), true);

	map.reset_finish({12, 12});

	EXPECT_EQ(map.exit_point(), Position(-1, -1));

	map.reset_finish({10, 10});

	EXPECT_EQ(map.exit_point(), Position(10, 10));
	EXPECT_EQ(map.start_point(), Position(1, 1));
}

TEST(GameFieldSuite, TestIsOnMap)
{
	GameField map(11, 11);

	EXPECT_EQ(map.is_on_map({10, 10}), true);
	EXPECT_EQ(map.is_on_map({0, -1}), false);
	EXPECT_EQ(map.is_on_map({11, 1}), false);
	EXPECT_EQ(map.is_on_map({11, 11}), false);
}

TEST(GameFieldSuite, TestMapCellEvents)
{
	auto *map = new GameField(11, 11);
	PlayerHandler handler(new Player);
	handler.register_observer(map);
	handler.set_position({4, 4});

	map->get_cell({5, 5}).add_event(EventFactory::instance().create(EVENT_TYPE::SPIKES));

	EXPECT_EQ(handler.get_health(), 100);

	handler.move_by_direction(DOWN, 1);
	handler.move_by_direction(RIGHT, 1);

	EXPECT_EQ(handler.get_health(), 80);

	delete map;
}

TEST(GameFieldSuite, TestDoorEvent)
{
	PlayerHandler handler(new Player);

	auto *map = new GameField(10, 10);
	map->reset_start({0, 0});
	map->reset_finish({7, 7});
	map->get_cell({1, 0}).add_event(EventFactory::instance().create(EVENT_TYPE::KEY));
	map->get_cell({0, 1}).add_event(EventFactory::instance().create(EVENT_TYPE::KEY));
	map->get_cell({1, 1}).add_event(EventFactory::instance().create(EVENT_TYPE::DOOR));

	handler.register_observer(map);
	handler.set_position({0, 0});

	map->print(std::cerr);

	EXPECT_EQ(handler.keys().empty(), true);
	EXPECT_EQ(map->can_move(&handler, {1, 1}), false);
	EXPECT_EQ(map->can_move(nullptr, {1, 1}), true);

	handler.move_by_direction(DOWN, 1);

	EXPECT_EQ(handler.keys().size(), 1);
	EXPECT_EQ(map->can_move(&handler, {1, 1}), true);

	map->print(std::cerr);

	delete map;
}