#pragma once
#include "Interface/EventInterface.hpp"
#include "Movement/Direction.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class RandomMine : public EventInterface {
  const int32_t power_lower_bound_ = 1;
  const int32_t power_upper_bound_ = 5;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] RandomMine *copy() const override;
  [[nodiscard]] RandomMine *create() const override;
};