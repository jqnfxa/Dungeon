#pragma once

#include "Handlers/Interface/EntityHandler.hpp"

class EventInterface {
 public:
  virtual ~EventInterface() = default;
  virtual void trigger(EntityHandler *handler) const = 0;
  [[nodiscard]] virtual bool is_temporary() const = 0;
  [[nodiscard]] virtual EventInterface *copy() const = 0;
  [[nodiscard]] virtual bool operator==(EventInterface *event) const = 0;
};