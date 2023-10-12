#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "RenderSlave.hpp"

class SimpleMenu : public RenderSlave {
  int32_t selected_ = 0;
  sf::RenderWindow &parent_;
  sf::Font &font_;
  sf::RectangleShape background_;
  std::vector<Button> buttons_;
 public:
  SimpleMenu(sf::RenderWindow &parent, sf::Font &font, const std::vector<std::pair<std::string, Command *>> &buttons, sf::Texture &texture);
  Command *on_key_press(const sf::Event &event) override;
  void on_exit() override;
  void render(const GameEngine &game) override;
  void scroll_down();
  void scroll_up();
  [[nodiscard]] Command *select_option() const;
};