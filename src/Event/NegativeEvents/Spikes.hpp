#pragma once
#include "Event/Interface/EventInterface.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class Spikes : public EventInterface {
  const int32_t no_armor_damage = 20;
  const int32_t armor_decrease_percent = 50;
  const int32_t critical_armor_value = 10;
  const double armor_decrease_multiplier = static_cast<double>(armor_decrease_percent) / 100.0;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Spikes *copy() const override;
  [[nodiscard]] Spikes *create() const override;
};