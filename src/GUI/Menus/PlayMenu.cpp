#include <iostream>
#include "PlayMenu.hpp"
#include "Command/Factory/CommandFactory.hpp"

PlayMenu::PlayMenu(Window &parent) : selected_(0), window_(parent)
{
	// load font
	if (!font_.loadFromFile("../../resources/fonts/arial.ttf"))
	{
		throw std::logic_error("Could not load font");
	}
	if (!texture_.loadFromFile("../../resources/assets/play_menu.png"))
	{
		throw std::logic_error("Could not load Main theme image");
	}

	default_ = sf::Color(sf::Color::White);
	chosen_ = sf::Color(sf::Color::Red);

	auto size = window_.render_object().getSize();

	auto text_size = size.y * 2 / 15;

	sf::Text new_game_button("New Game", font_, text_size);
	new_game_button.setPosition(size.x / 5, size.y / 5);

	sf::Text load_game_button("Load Save", font_, text_size);
	load_game_button.setPosition(size.x / 5, size.y / 5 + text_size + size.y / 10);

	sf::Text back_button("Back", font_, text_size);
	back_button.setPosition(size.x / 5, size.y / 5 + 2 * (text_size + size.y / 10));

	background_.setSize(sf::Vector2f(size.x, size.y));
	background_.setTexture(&texture_);
	background_.setPosition(0, 0);

	objects.push_back(std::move(new_game_button));
	objects.push_back(std::move(load_game_button));
	objects.push_back(std::move(back_button));
}

Command *PlayMenu::on_key_press(const sf::Event &event)
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
		if (selected_ < objects.size() - 1)
		{
			selected_++;
		}
	}
	else if (event.key.code == sf::Keyboard::Return)
	{
		if (selected_ == 0)
		{
			cmd = CommandFactory::instance().create(COMMAND::CREATE_SESSION);
		}
		else if (selected_ == 1)
		{
			std::cerr << "Load Save not implemented yet" << std::endl;
		}
		else if (selected_ == 2)
		{
			cmd = CommandFactory::instance().create(COMMAND::RETURN_TO_MENU);
		}
	}

	return cmd;
}

void PlayMenu::draw()
{
	window_.render_object().clear();


	window_.render_object().draw(background_);

	for (auto &element: objects)
	{
		element.setFillColor(default_);
	}
	objects[selected_].setFillColor(chosen_);

	for (auto &element: objects)
	{
		window_.render_object().draw(element);
	}


	window_.render_object().display();
}
