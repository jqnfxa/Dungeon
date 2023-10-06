#include "Menu.hpp"
#include "Command/Factory/CommandFactory.hpp"

Menu::Menu(sf::RenderWindow &parent,
		   int32_t buttons_count,
		   const std::vector<std::string> &buttons_names,
		   const std::vector<Command *> &buttons_commands,
		   const sf::Font &font, sf::Texture &background) : selected_(0),
								 window_(parent),
								 selected_color_(sf::Color(sf::Color::Red)),
								 default_color_(sf::Color(sf::Color::White))
{
	auto size = window_.getSize();
	auto initial = size.y / 20;
	auto left_padding = size.x / 5;
	auto text_size = size.y * 5 / 7 / (buttons_count + (buttons_count - 1) / 5);
	auto step = text_size / 5;

	for (int32_t i = 0, y = initial; i < buttons_count; ++i, y += text_size + step)
	{
		ActionTextButton button(buttons_names[i], font, text_size, buttons_commands[i]);
		button.set_position(left_padding, y);

		buttons_.push_back(std::move(button));
	}

	background_.setSize(sf::Vector2f(size.x, size.y));
	background_.setTexture(&background);
	background_.setPosition(0, 0);
}

Command *Menu::on_key_press(const sf::Event &event)
{
	Command *cmd = CommandFactory::instance().create(COMMAND::EMPTY_OPERATION);

	if (event.key.code == sf::Keyboard::Up)
	{
		if (selected_ > 0)
		{
			selected_--;
		}
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (selected_ < buttons_.size() - 1)
		{
			selected_++;
		}
	}
	else if (event.key.code == sf::Keyboard::Return)
	{
		cmd = buttons_[selected_].action();
	}

	return cmd;
}

void Menu::draw()
{
	window_.clear();

	window_.draw(background_);

	for (auto &element: buttons_)
	{
		element.button().setFillColor(default_color_);
	}
	buttons_[selected_].button().setFillColor(selected_color_);

	for (auto &element: buttons_)
	{
		window_.draw(element.button());
	}

	window_.display();
}