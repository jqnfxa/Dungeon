#include "SimpleMenu.hpp"

SimpleMenu::SimpleMenu(sf::RenderWindow &parent,
					   sf::Font &font,
					   const std::vector<std::pair<std::string, Command *>> &buttons,
					   sf::Texture &texture,
					   ALIGNMENT alignment) :
					   parent_(parent),
					   selected_(0),
					   font_(font)
{
	auto window_size = parent_.getSize();

	if (buttons.empty())
	{
		throw std::invalid_argument("Cannot create menu without buttons");
	}

	sf::Vector2u possible_size = window_size;
	const double coefficient = 0.25;
	auto button_y = static_cast<int32_t>(possible_size.y / (buttons.size() + coefficient * (buttons.size() - 1)));
	auto step = static_cast<int32_t>(button_y * coefficient);
	auto button_x = std::min(button_y * 4, static_cast<int32_t>(possible_size.x));
	sf::Vector2f button_size(static_cast<float>(button_x), static_cast<float>(button_y));
	const float alignment_x = alignment == CENTER ?
		window_size.x / 2 - button_size.x / 2 :
		(alignment == LEFT_SIDE ? 0 : window_size.x - button_size.x);

	for (size_t i = 0, dest = 0; i < buttons.size(); ++i, dest += step + button_y)
	{
		Button button(buttons[i].first, buttons[i].second, font_, button_size);
		button.setPosition(alignment_x, dest);
		buttons_.push_back(std::move(button));
	}

	// first label selected by default
	buttons_[0].mark_selected();

	background_.setSize(sf::Vector2f(window_size.x, window_size.y));
	background_.setTexture(&texture);
	background_.setPosition(0, 0);
}

Command *SimpleMenu::on_key_press(const sf::Event &event)
{
	Command *command = nullptr;

	switch (event.key.code)
	{
		case sf::Keyboard::Up: scroll_up();
			break;
		case sf::Keyboard::Down: scroll_down();
			break;
		case sf::Keyboard::Enter: command = select_option();
			break;
		default: command = nullptr;
	}

	return command;
}

void SimpleMenu::render(const GameEngine &game)
{
	parent_.clear();

	parent_.draw(background_);

	for (auto &button : buttons_)
	{
		parent_.draw(button);
	}

	parent_.display();
}

void SimpleMenu::scroll_down()
{
	if (selected_ < buttons_.size() - 1)
	{
		buttons_[selected_].mark_unselected();
		buttons_[++selected_].mark_selected();
	}
}

void SimpleMenu::scroll_up()
{
	if (selected_ > 0)
	{
		buttons_[selected_].mark_unselected();
		buttons_[--selected_].mark_selected();
	}
}

Command *SimpleMenu::select_option() const
{
	return buttons_[selected_].action();
}

void SimpleMenu::on_exit()
{
	buttons_.clear();
}