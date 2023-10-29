#pragma once

#include "Command/Interface/Interface.hpp"

class OpenDifficultyOptions : public Command {
 public:
  void execute(GameEngine &game) override;
  bool operator==(Command *other) override;
  [[nodiscard]] std::string to_str() const override;
};