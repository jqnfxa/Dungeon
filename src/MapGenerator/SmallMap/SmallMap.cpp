#include "SmallMap.hpp"
#include "Event/RandomMine.hpp"
#include "Event/Spikes.hpp"
#include "Event/Potion.hpp"
#include "MapGenerator/RandomLevelGen/Generator.hpp"

#include <iostream>

Map *SmallMap::generate()
{
	int m = 10;
	int n = 15;

	Generator gen(m, n, 20, 0.4 * m * n, 20, 70);

	return gen.generate();
}
