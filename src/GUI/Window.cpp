#include <iostream>
#include "Window.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/PlayMenu.hpp"
#include "Command/Factory/CommandFactory.hpp"
#include "GUI/Menus/GameFieldDrawer.hpp"

Window::Window(GameEngine &game, const sf::VideoMode &mode, const std::string &title, sf::Uint32 style) : game_engine_(game),
																										  window_(mode, title, style)
{
	available_[GameState::MAIN_MENU] = new MainMenu(*this);
	available_[GameState::PLAY_MENU] = new PlayMenu(*this);
	available_[GameState::PLAYING] = new GameFieldDrawer(*this);
	//available_[GameState::WIN_SCREEN] = available_[GameState::PLAYING];
	//available_[GameState::DEATH_SCREEN] = available_[GameState::PLAYING];

	// new menu ?
	// available_[GameState::HOLD_MENU] = ;
	// available_[GameState::SETTINGS] = ;
}

Window::~Window()
{
	for (auto &[key, value]: available_)
	{
		delete value;
	}
	window_.close();
}

sf::RenderWindow &Window::render_object()
{
	return window_;
}

Command *Window::process_input()
{
	sf::Event event{};
	if (window_.pollEvent(event))
	{
		auto *slave = available_[game_engine_.state().active()];

		if (event.type == sf::Event::Closed)
		{
			return CommandFactory::instance().create(COMMAND::TERMINATE);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			return slave->on_key_press(event);
		}
	}

	return CommandFactory::instance().create(COMMAND::EMPTY_OPERATION);
}

void Window::draw()
{
	if (state() != GameState::TERMINATE)
	{
		available_.at(game_engine_.state().active())->draw();
	}
}

GameState Window::state() const
{
	return game_engine_.state();
}
