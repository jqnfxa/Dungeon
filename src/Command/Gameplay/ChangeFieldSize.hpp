#pragma once

#include "Command/Interface/Interface.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class ChangeFieldSize : public Command {
  MAP_SIZE size_;
 public:
  explicit ChangeFieldSize(MAP_SIZE difficulty);
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};
