#pragma once

#include "Command/Interface/Interface.hpp"
#include "Movement/Direction.hpp"

class MovePlayer : public Command {
  const DIRECTION direction_;
 public:
  explicit MovePlayer(DIRECTION direction);
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};