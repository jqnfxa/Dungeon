#pragma once

#include "../Base/InputClass.hpp"

class SfmlRenderer;

class SfmlInput : public Input {
  SfmlRenderer *renderer_;
 public:
  explicit SfmlInput(const std::string &config_path);
  void init_renderer(SfmlRenderer *renderer);
  void update(GameState *game_state) override;
};
