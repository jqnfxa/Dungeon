#pragma once

class GameEngine;

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute(GameEngine &game) = 0;
  virtual bool operator==(Command *other) = 0;
};
