#pragma once

#include "Command/Interface/Interface.hpp"

class NOP : public Command {
 public:
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};
