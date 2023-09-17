#include "MediumMap.hpp"
#include "MapGenerator/RandomLevelGen/Generator.hpp"

Map *MediumMap::generate()
{
	int m = 30;
	int n = 50;

	Generator gen(m, n, 25, 0.4 * m * n, 30, 50);

	return gen.generate();
}
