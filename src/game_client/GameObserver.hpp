#pragma once


class GameEngine;
class GameObserver {
 public:
  virtual ~GameObserver() = default;
  virtual void update(const GameEngine &engine) = 0;
};
