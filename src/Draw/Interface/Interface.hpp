#pragma once

#include "Game/Engine/GameEngine.hpp"

class Renderer {
 public:
  virtual ~Renderer() = default;
  virtual void render(const GameEngine &game) = 0;
};