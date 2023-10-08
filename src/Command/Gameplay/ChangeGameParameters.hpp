#pragma once

#include "Command/Interface/Interface.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class ChangeGameParameters : public Command {
  MAP_SIZE size_;
  DIFFICULTY difficulty_;
 public:
  ChangeGameParameters(MAP_SIZE size, DIFFICULTY difficulty);
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};
