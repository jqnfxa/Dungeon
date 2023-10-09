#pragma once

#include "Command/Interface/Interface.hpp"

class Input {
 public:
  virtual ~Input() = default;
  virtual Command *command() = 0;
  virtual void update() = 0;
};