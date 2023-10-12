#pragma once

#include "Game/GameObserver.hpp"
#include "Draw/Interface/Interface.hpp"

class Tracker : public GameObserver {
  Renderer *renderer_;
 public:
  explicit Tracker(Renderer *renderer);
  void update(const GameEngine &engine) override;
};