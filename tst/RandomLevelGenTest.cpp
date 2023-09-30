#include <MapGenerator/RandomLevelGen/Generator.hpp>
#include <MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp>
#include "gtest/gtest.h"
#include "Entities/Player/Player.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "Event/Factory/EventFactory.hpp"

TEST(MapGeneratorSuite, TestSmallMapGeneration)
{
	PlayerHandler handler(new Player);
	EventFactory::instance().reset_player_reference(&handler);
	DefaultLevelGenerator gen(MEDIUM, AVERAGE);
	auto new_map = gen.generate();

	auto route = new_map->find_route(new_map->start_point(), new_map->exit_point());

	auto *copy = new GameField(*new_map);
	for (auto &cell : route)
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
/*

TEST(MapGeneratorSuite, TestMediumMapGeneration)
{
	int m = 80;
	int n = 150;

	Generator generator(m, n, 25, 30, 50, 20);
	GameField *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}

TEST(MapGeneratorSuite, TestBigMapGeneration)
{
	int m = 100;
	int n = 250;

	Generator generator(m, n, 25, 30, 50, 20);
	GameField *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}

TEST(MapGeneratorSuite, TestHugeMapGeneration)
{
	int m = 200;
	int n = 400;

	Generator generator(m, n, 100, 30, 50, 20);
	GameField *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}*/

/*
TEST(MapGeneratorSuite, TestMediumMapGeneration) {
	int m = 50;
	int n = 50;

	Generator generator(m, n, 30, 0.4 * m * n, 40, 30);
	Map *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}

TEST(MapGeneratorSuite, TestBigMapGeneration) {
	int m = 100;
	int n = 100;

	Generator generator(m, n, 50, 0.3 * m * n, 50, 20);
	Map *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}*/
/*
TEST(MapGeneratorSuite, TestHugeMapGeneration) {
	int m = 500;
	int n = 500;

	Generator generator(m, n, 50, 0.3 * m * n, 50, 20);
	Map *new_map = generator.generate();

	// new_map->print(std::cerr);

	delete new_map;
}*/