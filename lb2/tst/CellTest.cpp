#include <World/Cell.hpp>
#include "gtest/gtest.h"

TEST(CellTestSuite, TestDefaultConstructor)
{
	Cell cell;

	EXPECT_EQ(cell.is_movable(), true);
}

TEST(CellTestSuite, TestTypeConstructor)
{
	{
		Cell cell(Cell::Type::WALL);

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
	Cell other = std::move(cell);

	EXPECT_EQ(other.is_movable(), false);
	EXPECT_EQ(other.is_entrance(), false);
	EXPECT_EQ(other.is_exit(), false);
}
