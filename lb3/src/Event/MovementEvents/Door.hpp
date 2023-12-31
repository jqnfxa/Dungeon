#pragma once

#include "Event/Interface/EventInterface.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include <cstdint>

class Door : public EventInterface {
 private:
  const bool temporary_state_ = false;
  mutable bool is_open_ = false;

  const int64_t hash_required_;
 public:
  explicit Door(Key &key);
  bool is_open() const;
  void trigger(EntityHandler *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] Door *copy() const override;
  [[nodiscard]] bool operator==(EventInterface *event) const override;
};