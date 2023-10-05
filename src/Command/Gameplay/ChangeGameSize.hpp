#pragma once

#include "Command/Interface/Interface.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class ChangeGameSize : public Command {
  MAP_SIZE size_;
 public:
  ChangeGameSize(MAP_SIZE size);
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};
