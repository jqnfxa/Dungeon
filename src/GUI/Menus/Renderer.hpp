#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Command/Interface/Interface.hpp"

class Window;

class Renderer {
 public:
  virtual ~Renderer() = default;
  virtual Command *on_key_press(const sf::Event &event) = 0;
  virtual void draw() = 0;
};
