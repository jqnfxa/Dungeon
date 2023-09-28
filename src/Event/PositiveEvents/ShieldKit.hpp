#pragma once

#include "Event/Interface/EventInterface.hpp"
#include <cstdint>

class ShieldKit : public EventInterface {
  const int32_t shield_value = 50;
 public:
  void interaction(HandlerInterface *handler) const override;
  [[nodiscard]] bool is_temporary() const override;
  [[nodiscard]] ShieldKit *copy() const override;
  [[nodiscard]] ShieldKit *create() const override;
};
