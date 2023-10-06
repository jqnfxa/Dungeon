#include <iostream>
#include "Window.hpp"
#include "Command/Factory/CommandFactory.hpp"
#include "GUI/Menus/GameFieldDrawer.hpp"

Window::Window(GameEngine &game, const sf::VideoMode &mode, const std::string &title, sf::Uint32 style) : game_engine_(game),
																										  window_(mode, title, style)
{
	if (!font_.loadFromFile("../../resources/fonts/arial.ttf"))
	{
		throw std::logic_error("Failed to load font");
	}
	if (!main_menu_texture_.loadFromFile("../../resources/assets/main_menu.png"))
	{
		throw std::logic_error("Failed to load Main theme image");
	}
	if (!play_menu_texture_.loadFromFile("../../resources/assets/play_menu.png"))
	{
		throw std::logic_error("Failed to load Play menu image");
	}

	available_[GameState::MAIN_MENU] = new Menu(window_, 2, {"Play", "Exit"}, {
		CommandFactory::instance().create(COMMAND::OPEN_PLAY_MENU),
		CommandFactory::instance().create(COMMAND::TERMINATE)}, font_, main_menu_texture_);
	available_[GameState::PLAY_MENU] = new Menu(window_, 3, {"New game", "Load", "Back"}, {
		CommandFactory::instance().create(COMMAND::CREATE_SESSION),
		CommandFactory::instance().create(COMMAND::EMPTY_OPERATION),
		CommandFactory::instance().create(COMMAND::RETURN_TO_MENU)}, font_, play_menu_texture_);

	available_[GameState::HOLD_MENU] = new Menu(window_, 2, {"Continue", "Exit"}, {
		CommandFactory::instance().create(COMMAND::CREATE_SESSION),
		CommandFactory::instance().create(COMMAND::RETURN_TO_MENU)}, font_, play_menu_texture_);

	//available_[GameState::PLAYING] = new GameFieldDrawer(*this);

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
