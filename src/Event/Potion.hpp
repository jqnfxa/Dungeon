#pragma once
#include "Interface/EventInterface.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class Potion : public EventInterface {
 private:
  const int32_t health_increase = 50;
  const int32_t attack_increase = 10;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] Potion *copy() const override;
  [[nodiscard]] Potion *create() const override;
};
