#include <iostream>
#include "SfmlRenderer.hpp"
#include "SimpleMenu.hpp"
#include "Game/State/MainMenuState.hpp"
#include "Game/State/PlayMenuState.hpp"
#include "Game/State/TerminateState.hpp"

SfmlRenderer::SfmlRenderer(SfmlInput &input) : window_(sf::VideoMode(screen_width_, screen_height_), "DungeonGame"), input_(input)
{
	load_data();
	window_.setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Play", input.command("play")},
									  {"Settings", input.command("options")},
									  {"Exit", input.command("terminate")}},
									  textures_[0]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"New Game", input.command("create")},
									  {"Load", nullptr},
									  {"Back", input.command("menu")}},
									  textures_[1]));

	suitable_for_state_[std::type_index(typeid(MainMenuState))] = 0;
	suitable_for_state_[std::type_index(typeid(PlayMenuState))] = 1;
}

sf::Image SfmlRenderer::load_image(const std::string &path)
{
	sf::Image image;
	if (!image.loadFromFile(path))
	{
		destroy();
		throw std::invalid_argument(std::string("Could not find: ") + path);
	}
	return image;
}

sf::Font SfmlRenderer::load_font(const std::string &path)
{
	sf::Font font;
	if (!font.loadFromFile(path))
	{
		destroy();
		throw std::invalid_argument(std::string("Could not find: ") + path);
	}
	return font;
}

sf::Texture SfmlRenderer::load_texture(const std::string &path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		destroy();
		throw std::invalid_argument(std::string("Could not find: ") + path);
	}
	return texture;
}

void SfmlRenderer::load_data()
{
	// TODO load all data related to textures/fonts/etc
	//icon_ = std::move(load_image(icon_path));
	//font_ = std::move(load_font(font_path));
	font_.loadFromFile(std::string("../../resources/") + "arial.ttf");

	textures_.push_back(sf::Texture());
	textures_.push_back(sf::Texture());
	textures_[0].loadFromFile(std::string("../../resources/") + "assets/main_theme.png");
	textures_[1].loadFromFile(std::string("../../resources/") + "assets/play_menu.png");
	//textures_.push_back(std::move(load_texture(main_menu_path)));
	//textures_.push_back(std::move(load_texture(play_menu_path)));
}

SfmlRenderer::~SfmlRenderer()
{
	destroy();
}

void SfmlRenderer::render(const GameEngine &game)
{
	if (game.state() == nullptr || typeid(*game.state()) == typeid(TerminateState))
	{
		return;
	}

	auto state = std::type_index(typeid(*game.state()));
	if (suitable_for_state_.find(state) == suitable_for_state_.end())
	{
		destroy();
		throw std::logic_error("Cannot find suitable slave for state: " + game.state()->to_str());
	}

	slaves_[suitable_for_state_[state]]->render(game);
}

Command *SfmlRenderer::retrieve_input(GameState *game_state)
{
	if (game_state == nullptr)
	{
		return nullptr;
	}

	auto state = std::type_index(typeid(*game_state));
	if (suitable_for_state_.find(state) == suitable_for_state_.end())
	{
		destroy();
		throw std::logic_error("Cannot find suitable slave for state: " + game_state->to_str());
	}

	Command *command = nullptr;

	sf::Event event{};
	if (window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				destroy();
				return input_.command("terminate");
			case sf::Event::KeyPressed:
				return slaves_[suitable_for_state_[state]]->on_key_press(event);
			default:
				// we don't process other commands
				command = nullptr;
		}
	}

	return command;
}

void SfmlRenderer::destroy()
{
	for (auto &slave : slaves_)
	{
		if (slave != nullptr)
		{
			slave->on_exit();
		}
		delete slave;
		slave = nullptr;
	}
	slaves_.clear();
	suitable_for_state_.clear();
}
