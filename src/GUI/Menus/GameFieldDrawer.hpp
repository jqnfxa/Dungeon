#pragma once

#include "Interface/Menu.hpp"
#include "../Window.hpp"

class GameFieldDrawer : public Menu {
  Window &window_;

  std::vector<std::vector<sf::RectangleShape>> render_map_;
 public:
  explicit GameFieldDrawer(Window &parent);
  Command *on_key_press(const sf::Event &event) override;
  void draw() override;
};
