#pragma once

#include "Event/Interface/EventInterface.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class Star : public EventInterface {
 private:
  const int32_t xp_amount = 100;
  const bool temporary_state_ = true;

  PlayerHandler &handler_;
 public:
  explicit Star(PlayerHandler &handler);
  void trigger() const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Star *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};