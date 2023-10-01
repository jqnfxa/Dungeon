#include <World/Cell.hpp>
#include "gtest/gtest.h"
#include "Event/Factory/EventFactory.hpp"

TEST(CellTestSuite, TestDefaultConstructor)
{
	Cell cell;

	EXPECT_EQ(cell.is_movable(), true);
}

TEST(CellTestSuite, TestTypeConstructor)
{
	{
		Cell cell(Cell::TYPE::WALL);
		cell.add_event(EventFactory::instance().create(EVENT_TYPE::SPIKES));
		cell.remove_event();
		cell.add_event(EventFactory::instance().create(EVENT_TYPE::RANDOM_MINE));

		EXPECT_EQ(cell.is_movable(), false);
		EXPECT_EQ(cell.is_entrance(), false);
		EXPECT_EQ(cell.is_exit(), false);
	}
	{
		Cell cell(Cell::TYPE::ENTRANCE);

		EXPECT_EQ(cell.is_movable(), true);
		EXPECT_EQ(cell.is_entrance(), true);
	}
}

TEST(CellTestSuite, TestCopyConstructor)
{

	Cell cell(Cell::TYPE::WALL);
	cell.add_event(EventFactory::instance().create(EVENT_TYPE::SPIKES));
	Cell other = cell;
	other.add_event(EventFactory::instance().create(EVENT_TYPE::SHIELD_KIT));

	EXPECT_EQ(other.is_movable(), false);
	EXPECT_EQ(other.is_entrance(), false);
	EXPECT_EQ(other.is_exit(), false);
}

TEST(CellTestSuite, TestMoveConstructor)
{

	Cell cell(Cell::TYPE::WALL);
	cell.add_event(EventFactory::instance().create(EVENT_TYPE::SPIKES));
	Cell other = std::move(cell);

	EXPECT_EQ(other.is_movable(), false);
	EXPECT_EQ(other.is_entrance(), false);
	EXPECT_EQ(other.is_exit(), false);
}