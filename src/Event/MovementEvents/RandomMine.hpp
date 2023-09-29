#pragma once
#include "Event/Interface/EventInterface.hpp"
#include "Movement/Direction.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class RandomMine : public EventInterface {
  const int32_t power_lower_bound_ = 1;
  const int32_t power_upper_bound_ = 3;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] RandomMine *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};