#pragma once

#include "Input/Interface/InputClass.hpp"
#include "GUI/Window.hpp"
#include <SFML/Graphics.hpp>

class SFMLInput : public Input {
  Window &window_;

  Command *last_command_;
 public:
  explicit SFMLInput(Window &window);
  Command* command() override;
  void update() override;
};
