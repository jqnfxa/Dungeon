#include "Random.hpp"
#include <random>

Random &Random::get_instance()
{
	static Random random;
	return random;
}
DIRECTION Random::pick_direction() const
{
	return static_cast<DIRECTION>(pick_num(1, 4));
}
int32_t Random::pick_num(int32_t from, int32_t to) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int32_t> distribution(from, to);

	return distribution(gen);
}
