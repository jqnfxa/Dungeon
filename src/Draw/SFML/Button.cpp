#include "Button.hpp"

Button::Button(const std::string &text,
			   Command *command,
			   sf::Font &font,
			   const sf::Vector2f &size,
			   const sf::Color &unselected,
			   const sf::Color &selected)
			   : command_(command),
			   default_color_(unselected),
			   selected_color_(selected),
			   font_(font),
			   text_()
{
	text_.setString(text);
	text_.setFont(font_);

	text_.setCharacterSize(size.y / 2);
	text_.setFillColor(default_color_);

	// center the text on the button
	sf::FloatRect textRect = text_.getLocalBounds();
	text_.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text_.setPosition(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
}

void Button::mark_selected()
{
	change_color(selected_color_);
}

void Button::mark_unselected()
{
	change_color(default_color_);
}

void Button::change_color(const sf::Color &new_color)
{
	text_.setFillColor(new_color);
}

Command *Button::action() const
{
	return command_;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text_, states);
}
