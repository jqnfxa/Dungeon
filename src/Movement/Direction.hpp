#pragma once
#include "../Math/Vector2.hpp"
#include "../Entities/Interface/EntityInterface.hpp"
#include <vector>

enum DIRECTION {
	none, left_up, up, right_up, right, right_bottom, down, left_down, left
};

class Direction {
 private:
  const std::vector<Vector2<int32_t>> possible_moves_ = {{0,  0},
														 {-1, -1},
														 {-1, 0},
														 {-1, 1},
														 {0,  1},
														 {1,  1},
														 {1,  0},
														 {1,  -1},
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
  Position calculate_position(const Position &old, const DIRECTION &direction);
};