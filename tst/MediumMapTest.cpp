#include "gtest/gtest.h"
#include "MapGenerator/MediumMap/MediumMap.hpp"

TEST(MapGeneratorSuit, TestGenerateSecondLevel) {
	MediumMap gen;
	Map *map = gen.generate();
	map->print(std::cerr);
	delete map;
}