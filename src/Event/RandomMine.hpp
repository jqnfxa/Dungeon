#pragma once
#include "Interface/EventInterface.hpp"
#include "Movement/Direction.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class RandomMine : public EventInterface {
  DIRECTION pick_direction() const;
  int32_t pick_power() const;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] RandomMine *copy() const override;
  [[nodiscard]] RandomMine *create() const override;
};