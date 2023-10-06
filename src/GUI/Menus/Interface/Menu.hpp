#pragma once

#include <SFML/Graphics.hpp>
#include "Command/Interface/Interface.hpp"

class Menu {
 public:
  virtual ~Menu() = default;
  virtual Command *on_key_press(const sf::Event &event) = 0;
  virtual void draw() = 0;
};