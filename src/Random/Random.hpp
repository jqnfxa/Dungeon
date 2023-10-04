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
  Random(const Random &) = delete;
  Random &operator=(const Random &) = delete;

  static Random &instance()
  {
	  static Random instance_;
	  return instance_;
  }
  [[nodiscard]] DIRECTION pick_direction() const;
  [[nodiscard]] EventInterface *pick_event(EVENT_GROUP group) const;

  template <typename Int>
  [[nodiscard]] Int pick_num(Int from, Int to) const
  {
	  std::random_device rd;
	  std::mt19937 gen(rd());
	  std::uniform_int_distribution<Int> distribution(from, to);

	  return distribution(gen);
  }

  template <class LegacyRandomAccessIterator>
  [[nodiscard]] inline typename LegacyRandomAccessIterator::value_type pick_from_range(LegacyRandomAccessIterator begin, LegacyRandomAccessIterator end) const
  {
	  return *std::next(begin, pick_num<int64_t>(0, std::distance(begin, end) - 1));
  }
};
