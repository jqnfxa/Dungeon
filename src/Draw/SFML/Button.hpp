#pragma once

#include "SfmlRenderer.hpp"

class Button : public sf::Drawable, public sf::Transformable {
 private:
  Command *command_;
  sf::Color default_color_;
  sf::Color selected_color_;
  sf::Font &font_;
  sf::Text text_;
 public:
  Button(const std::string& text,
		 Command *command,
		 sf::Font &font,
		 const sf::Vector2f &size,
		 const sf::Color &default_color = sf::Color(sf::Color::White),
		 const sf::Color &selected_color = sf::Color(sf::Color::Red));
  void mark_selected();
  void mark_unselected();
  void change_color(const sf::Color &new_color);
  Command *action() const;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
