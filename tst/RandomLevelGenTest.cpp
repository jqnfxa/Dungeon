#include <MapGenerator/RandomLevelGen/Generator.hpp>
#include "gtest/gtest.h"
#include "Event/RandomMine.hpp"

TEST(MapGeneratorSuite, TestSmallMapGeneration) {
	int m = 10;
	int n = 10;

	Generator generator(m, n, 35, 0.4 * m * n, 10, 70);
	Map *new_map = generator.generate();

	new_map->print(std::cerr);

	delete new_map;
}

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
}
/*
TEST(MapGeneratorSuite, TestHugeMapGeneration) {
	int m = 500;
	int n = 500;

	Generator generator(m, n, 50, 0.3 * m * n, 50, 20);
	Map *new_map = generator.generate();

	// new_map->print(std::cerr);

	delete new_map;
}*/