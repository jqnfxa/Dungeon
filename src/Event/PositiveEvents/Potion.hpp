#pragma once
#include "Event/Interface/EventInterface.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cstdint>

// TODO think about more interesting interaction
class Potion : public EventInterface {
 private:
  const int32_t health_increase = 50;
  const int32_t attack_increase = 10;
  const bool temporary_state_ = true;

  PlayerHandler &handler_;
 public:
  explicit Potion(PlayerHandler &handler);
  void trigger() const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Potion *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};
