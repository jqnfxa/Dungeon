#pragma once
#include "../Math/Vector2.hpp"
#include "../Entities/Interface/EntityInterface.hpp"
#include <vector>

enum DIRECTION {
	NONE, UP, RIGHT, DOWN, LEFT
};

class Direction {
 private:
  const std::vector<Vector2<int32_t>> possible_moves_ = {{0,  0},
														 {-1, 0},
														 {0,  1},
														 {1,  0},
														 {0,  -1}};
  Direction() = default;
 public:
  Direction(const Direction &) = delete;
  void operator=(const Direction &) = delete;

  static Direction &getInstance()
  {
	  static Direction instance;
	  return instance;
  }
  Position calculate_position(const Position &old, DIRECTION direction);
};