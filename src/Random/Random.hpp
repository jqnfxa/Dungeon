#pragma once

#include "Movement/Direction.hpp"
#include "Event/Interface/EventInterface.hpp"
#include <random>

enum EVENT_TYPE
{
	NEGATIVE = -1,
	NEUTRAL,
	POSITIVE
};

class Random {
  Random() = default;
 public:
  static Random &get_instance();
  [[nodiscard]] DIRECTION pick_direction() const;
  [[nodiscard]] int32_t pick_num(int32_t from, int32_t to) const;
  [[nodiscard]] EventInterface *pick_event(EVENT_TYPE type);
};
