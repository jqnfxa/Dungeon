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
	load_textures();

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

	available_[GameState::PLAYING] = new GameFieldDrawer(window_, game_engine_, textures_);

	available_[GameState::WIN_SCREEN] = new Menu(window_, 2, {"Next level", "Exit"}, {
		CommandFactory::instance().create(COMMAND::CREATE_SESSION),
		CommandFactory::instance().create(COMMAND::RETURN_TO_MENU)}, font_, play_menu_texture_);

	available_[GameState::DEATH_SCREEN] = new Menu(window_, 2, {"Restart", "Exit"}, {
		CommandFactory::instance().create(COMMAND::RESTART_SESSION),
		CommandFactory::instance().create(COMMAND::RETURN_TO_MENU)}, font_, play_menu_texture_);

	// new menu ?
	// available_[GameState::SETTINGS] = ;
}

Window::~Window()
{
	for (auto &[key, value]: available_)
	{
		// TODO possible leak here?
		delete value;
		value = nullptr;
	}
	available_.clear();
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

void Window::load_textures()
{
	if (!main_menu_texture_.loadFromFile("../../resources/assets/main_menu.png"))
	{
		throw std::logic_error("Failed to load Main theme image");
	}
	if (!play_menu_texture_.loadFromFile("../../resources/assets/play_menu.png"))
	{
		throw std::logic_error("Failed to load Play menu image");
	}
	if (!win_screen_texture_.loadFromFile("../../resources/assets/win.png"))
	{
		throw std::logic_error("Failed to load win menu image");
	}
	if (!death_screen_texture_.loadFromFile("../../resources/assets/lose.png"))
	{
		throw std::logic_error("Failed to load win menu image");
	}
	if (!play_menu_texture_.loadFromFile("../../resources/assets/play_menu.png"))
	{
		throw std::logic_error("Failed to load Play menu image");
	}
	if (!textures_[IS_CLOSED].loadFromFile("../../resources/assets/wall.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[IS_OPEN].loadFromFile("../../resources/assets/empty_cell.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[IS_START].loadFromFile("../../resources/assets/start.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[IS_FINISH].loadFromFile("../../resources/assets/finish.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_SPIKES].loadFromFile("../../resources/assets/spikes.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_POTION].loadFromFile("../../resources/assets/potion.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_SHIELD_KIT].loadFromFile("../../resources/assets/shield.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_STAR].loadFromFile("../../resources/assets/star.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_RANDOM_MINE].loadFromFile("../../resources/assets/random_mine.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_KEY].loadFromFile("../../resources/assets/key.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[HAS_DOOR].loadFromFile("../../resources/assets/door.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[DOOR_LOCKED].loadFromFile("../../resources/assets/lock.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
	if (!textures_[PLAYER].loadFromFile("../../resources/assets/player.png"))
	{
		throw std::logic_error("Failed to load gameplay textures");
	}
}