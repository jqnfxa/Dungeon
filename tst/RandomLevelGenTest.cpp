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
	EventFactory::instance().reset_player_reference(&handler);
	DefaultLevelGenerator gen(SMALL, AVERAGE);
	auto new_map = gen.generate();

	auto route = new_map->find_route(new_map->start_point(), new_map->exit_point());

	auto *copy = new GameField(*new_map);
	for (auto &cell: route)
	{
		if (cell != copy->start_point() && cell != copy->exit_point())
		{
			copy->get_cell(cell).set_type(Cell::TYPE::PATH_PART);
		}
	}

	new_map->print(std::cerr);
	delete new_map;

	copy->print(std::cerr);
	delete copy;
}

TEST(MapGeneratorSuite, TestMaxMapGeneration)
{
	PlayerHandler handler(new Player);
	EventFactory::instance().reset_player_reference(&handler);
	Generator gen(100, 100, 0, 50, 50, 0);
	auto new_map = gen.generate();

	{
		Timer time(std::cerr, "A* search");

		for (int i = 0; i < 100; ++i)
		{
			auto route = new_map->find_route(new_map->start_point(), new_map->exit_point());
		}
	}

	//new_map->print(std::cerr);
	delete new_map;
}