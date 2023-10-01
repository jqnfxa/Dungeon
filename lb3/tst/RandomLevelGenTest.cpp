#include <MapGenerator/RandomLevelGen/Generator.hpp>
#include <MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp>
#include "gtest/gtest.h"
#include "Entities/Player/Player.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "Event/Factory/EventFactory.hpp"
#include "Profiler/Timer.hpp"

TEST(MapGeneratorSuite, TestSmallMapGeneration)
{
	PlayerHandler handler(new Player);
	DefaultLevelGenerator gen(MEDIUM, AVERAGE);
	auto new_map = gen.generate();

	auto route = new_map->find_route(nullptr, new_map->start_point(), new_map->exit_point());

	auto *copy = new GameField(*new_map);
	for (auto &cell: route)
	{
		if (cell != copy->start_point() && cell != copy->exit_point())
		{
			copy->get_cell(cell).set_type(Cell::TYPE::PATH_PART);
			copy->get_cell(cell).remove_event();
		}
	}

	new_map->print(std::cerr);
	delete new_map;

	copy->print(std::cerr);
	delete copy;
}

TEST(MapGeneratorSuite, TestMaxMapGeneration)
{
	Generator gen(1000, 1000, 80, 50, 50, 0);
	auto new_map = gen.generate();
	delete new_map;
}