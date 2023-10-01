#pragma once
#include "../Math/Vector2.hpp"
#include "../Entities/Interface/EntityInterface.hpp"
#include <vector>

enum DIRECTION {
	NONE, UP, RIGHT, DOWN, LEFT
};

class Direction {
 private:
  std::vector<Position> possible_moves_ = {{0, 0}};
  std::vector<Position> possible_moves_sharable = {{-1, 0},
												   {0,  1},
												   {1,  0},
												   {0,  -1}};
  Direction();
 public:
  Direction(const Direction &) = delete;
  Direction &operator=(const Direction &) = delete;

  static Direction &instance()
  {
	  static Direction instance_;
	  return instance_;
  }
  [[nodiscard]] const std::vector<Position> &get_all_possible_moves() const;
  Position calculate_position(const Position &old, DIRECTION direction);
};