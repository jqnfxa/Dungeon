#include <iostream>
#include "MainMenu.hpp"
#include "Command/Factory/CommandFactory.hpp"

MainMenu::MainMenu(Window &parent) : selected_(0), window_(parent)
{
	// load font
	if (!font_.loadFromFile("../../resources/fonts/arial.ttf"))
	{
		throw std::logic_error("Could not load font");
	}
	if (!texture_.loadFromFile("../../resources/assets/main_menu.png"))
	{
		throw std::logic_error("Could not load Main theme image");
	}

	default_ = sf::Color(sf::Color::White);
	chosen_ = sf::Color(sf::Color::Red);

	auto size = window_.render_object().getSize();

	sf::Text playButton("Play", font_, size.y / 5);
	playButton.setPosition(size.x / 5, size.y / 5);

	sf::Text exitButton("Exit", font_, size.y / 5);
	exitButton.setPosition(size.x / 5, size.y / 5 * 3);

	background_.setSize(sf::Vector2f(size.x, size.y));
	background_.setTexture(&texture_);
	background_.setPosition(0, 0);

	objects.push_back(std::move(playButton));
	objects.push_back(std::move(exitButton));
}

Command *MainMenu::on_key_press(const sf::Event &event)
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
			cmd = CommandFactory::instance().create(COMMAND::OPEN_PLAY_MENU);
		}
		else if (selected_ == 1)
		{
			cmd = CommandFactory::instance().create(COMMAND::TERMINATE);
		}
	}

	return cmd;
}

void MainMenu::draw()
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