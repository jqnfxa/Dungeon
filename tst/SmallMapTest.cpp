#include <MapGenerator/SmallMap/SmallMap.hpp>
#include "gtest/gtest.h"

TEST(MapGeneratorSuit, TestGenerateFirstLevel) {
	SmallMap gen;
	Map *map = gen.generate();
	// map->print(std::cerr);
	delete map;
}