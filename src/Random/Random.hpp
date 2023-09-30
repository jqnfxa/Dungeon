#pragma once

#include "Movement/Direction.hpp"
#include "Event/Interface/EventInterface.hpp"
#include <random>

enum EVENT_GROUP
{
	NEGATIVE = -1,
	NEUTRAL,
	POSITIVE
};

class Random {
  Random() = default;
 public:
  static Random &instance()
  {
	  static Random instance_;
	  return instance_;
  }
  [[nodiscard]] DIRECTION pick_direction() const;
  [[nodiscard]] int32_t pick_num(int32_t from, int32_t to) const;
  [[nodiscard]] EventInterface *pick_event(EVENT_GROUP group);

  template <class LegacyRandomAccessIterator>
  [[nodiscard]] inline typename LegacyRandomAccessIterator::value_type pick_from_range(LegacyRandomAccessIterator begin, LegacyRandomAccessIterator end) const
  {
	  return *std::next(begin, pick_num(0, std::distance(begin, end) - 1));
  }
};
