#pragma once
#include "Event/Interface/EventInterface.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class Star : public EventInterface {
  const int32_t xp_amount = 100;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Star *copy() const override;
  [[nodiscard]] Star *create() const override;
};