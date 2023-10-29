#pragma once

#include "GameState.hpp"

class DifficultyChangeState : public GameState {
 public:
  bool handle_command(GameEngine &game, Command *command) override;
  [[nodiscard]] std::string to_str() const override;
};