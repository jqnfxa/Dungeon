#pragma once

#include "Movement/Direction.hpp"
#include <random>

class Random {
  Random() = default;
 public:
  static Random &get_instance();
  [[nodiscard]] DIRECTION pick_direction() const;
  [[nodiscard]] int32_t pick_num(int32_t from, int32_t to) const;
};
