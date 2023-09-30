#pragma once

#include "Event/Interface/EventInterface.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cstdint>

class ShieldKit : public EventInterface {
  const int32_t shield_value = 50;
  const bool temporary_state_ = true;

  PlayerHandler &handler_;
 public:
  explicit ShieldKit(PlayerHandler &handler);
  void trigger() const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] ShieldKit *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};
