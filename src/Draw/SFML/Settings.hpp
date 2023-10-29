#pragma once

#include <SFML/Graphics/Text.hpp>
#include "RenderSlave.hpp"
#include "Button.hpp"

class Settings : public RenderSlave {
  int32_t selected_;
  sf::RenderWindow &parent_;
  sf::Font &font_;
  SfmlInput &input_;

  std::vector<std::pair<sf::Text, std::pair<int32_t, std::vector<Button>>>> labels_;
 public:
  Settings(sf::RenderWindow &parent, sf::Font &font, SfmlInput &input);
  Command *on_key_press(const sf::Event &event);
  void scroll_down();
  void scroll_up();
  void scroll_right();
  void scroll_left();
};