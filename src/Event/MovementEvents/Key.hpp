#pragma once

#include "Event/Interface/EventInterface.hpp"
#include <cstdint>

class PlayerHandler;

class Key : public EventInterface {
 private:
  const bool temporary_state_ = true;

  const int64_t hash_;
  PlayerHandler &handler_;
 public:
  explicit Key(PlayerHandler &handler);
  [[nodiscard]] int64_t hash() const;
  void trigger() const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Key *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};