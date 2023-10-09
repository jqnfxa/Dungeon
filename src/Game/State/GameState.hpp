#pragma once

#include "Command/Interface/Interface.hpp"
#include <string>

class GameState {
 public:
  virtual ~GameState() = default;
  virtual bool handle_command(GameEngine &game, Command *command) = 0;
  [[nodiscard]] virtual std::string to_str() const = 0;
};
