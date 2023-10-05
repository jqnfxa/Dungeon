#pragma once

#include "Command/Interface/Interface.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class ChangeGameDifficulty : public Command {
  DIFFICULTY difficulty_;
 public:
  ChangeGameDifficulty(DIFFICULTY difficulty);
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
};
