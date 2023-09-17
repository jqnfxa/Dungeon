#include "Random.hpp"
#include <random>

Random &Random::get_instance()
{
	static Random random;
	return random;
}
DIRECTION Random::pick_direction() const
{
	// TODO don't forget to change picking if only 4 moves will possible
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int16_t> distribution(1, 8);

	int16_t dir = 0;
	while (dir == 0 || dir % 2)
	{
		dir = distribution(gen);
	}

	return static_cast<DIRECTION>(dir);
}
int32_t Random::pick_num(int32_t from, int32_t to) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int32_t> distribution(from, to);

	return distribution(gen);
}
