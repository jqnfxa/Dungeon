#pragma once

#include "Interface/Menu.hpp"
#include "../Window.hpp"

class MainMenu : public Menu {
  int16_t selected_;
  Window &window_;

  std::vector<sf::Text> objects;

  sf::Font font_;
  sf::Texture texture_;
  sf::RectangleShape background_;

  sf::Color default_;
  sf::Color chosen_;
 public:
  explicit MainMenu(Window &parent);
  Command *on_key_press(const sf::Event &event) override;
  void draw() override;
};
