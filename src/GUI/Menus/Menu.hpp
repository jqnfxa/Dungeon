#pragma once

#include "Command/Interface/Interface.hpp"
#include "GUI/Window.hpp"
#include "ActionTextButton.hpp"

class Menu {
  int16_t selected_;
  sf::RenderWindow &window_;
  sf::Color selected_color_;
  sf::Color default_color_;

  sf::RectangleShape background_;
  std::vector<ActionTextButton> buttons_;
 public:
  Menu() = delete;
  Menu(const Menu &) = delete;
  Menu(Menu &&) = delete;
  explicit Menu(sf::RenderWindow &parent,
				int32_t buttons_count,
				const std::vector<std::string> &buttons_names,
				const std::vector<Command *> &buttons_commands,
				const sf::Font &font,
				sf::Texture &background);
  Command *on_key_press(const sf::Event &event);
  void draw();
};