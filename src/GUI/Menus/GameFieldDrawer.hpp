#pragma once

#include "Menu.hpp"
#include "../Window.hpp"

class GameFieldDrawer {
  Window &window_;

  std::vector<std::vector<sf::RectangleShape>> render_map_;
 public:
  explicit GameFieldDrawer(Window &parent);
  Command *on_key_press(const sf::Event &event);
  void draw();
};
