#pragma once

#include <SFML/Graphics.hpp>
#include "Command/Interface/Interface.hpp"

class ActionTextButton {
  sf::Text text_;
  Command *cmd;
 public:
  ActionTextButton(const std::string &name, const sf::Font &font, const int32_t size, Command *action);
  void set_position(float x, float y);
  Command *action() const;
  sf::Text &button();
};