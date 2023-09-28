#pragma once
#include "../../Handlers/Interface/HandlerInterface.hpp"

class EventInterface {
 public:
  virtual ~EventInterface() = default;
  virtual void interaction(HandlerInterface *handler) const = 0;
  [[nodiscard]] virtual bool is_temporary() const = 0;
  [[nodiscard]] virtual EventInterface *copy() const = 0;
  [[nodiscard]] virtual EventInterface *create() const = 0;
};