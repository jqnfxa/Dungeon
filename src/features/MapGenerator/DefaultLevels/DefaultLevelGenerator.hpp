#pragma once

#include "../RandomLevelGen/Generator.hpp"

enum MAP_SIZE
{
	SMALL,
	MEDIUM,
	BIG,
	HUGE
};

enum DIFFICULTY
{
	EASY,
	AVERAGE,
	HARD
};

class DefaultLevelGenerator {
 private:
  MAP_SIZE size_;
  DIFFICULTY difficulty_;
 public:
  DefaultLevelGenerator() = delete;
  DefaultLevelGenerator(MAP_SIZE size, DIFFICULTY difficulty);
  [[nodiscard]] GameField *generate() const;
};
