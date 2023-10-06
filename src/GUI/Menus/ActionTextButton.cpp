#include "ActionTextButton.hpp"

ActionTextButton::ActionTextButton(const std::string &name, const sf::Font &font, const int32_t size, Command *action)
{
	text_.setString(name);
	text_.setFont(font);
	text_.setCharacterSize(size);
	cmd = action;
}

void ActionTextButton::set_position(float x, float y)
{
	text_.setPosition(x, y);
}

Command *ActionTextButton::action() const
{
	return cmd;
}

sf::Text &ActionTextButton::button()
{
	return text_;
}