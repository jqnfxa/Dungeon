#include <World/Cell.hpp>
#include "gtest/gtest.h"
#include "Event/Spikes.hpp"
#include "Event/RandomMine.hpp"

TEST(CellTestSuite, TestDefaultConstructor)
{
	Cell cell;

	EXPECT_EQ(cell.is_movable(), true);
}

TEST(CellTestSuite, TestTypeConstructor)
{
	{
		Cell cell(Cell::Type::WALL);
		cell.add_event(new Spikes);
		cell.remove_event();
		cell.add_event(new RandomMine);

		EXPECT_EQ(cell.is_movable(), false);
		EXPECT_EQ(cell.is_entrance(), false);
		EXPECT_EQ(cell.is_exit(), false);
	}
	{
		Cell cell(Cell::Type::ENTRANCE);

		EXPECT_EQ(cell.is_movable(), true);
		EXPECT_EQ(cell.is_entrance(), true);
	}
}

TEST(CellTestSuite, TestMoveConstructor)
{

	Cell cell(Cell::Type::WALL);
	cell.add_event(new Spikes);
	Cell other = std::move(cell);

	EXPECT_EQ(other.is_movable(), false);
	EXPECT_EQ(other.is_entrance(), false);
	EXPECT_EQ(other.is_exit(), false);
}