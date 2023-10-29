#pragma once

#include "Event/Interface/EventInterface.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cstdint>

class RandomMine : public EventInterface {
 private:
  const int32_t power_lower_bound_ = 0;
  const int32_t power_upper_bound_ = 2;
  const bool temporary_state_ = false;
 public:
  void trigger(EntityHandler *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] RandomMine *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};