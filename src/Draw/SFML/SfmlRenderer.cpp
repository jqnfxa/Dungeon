#include <iostream>
#include <vector>
#include <string>
#include "SfmlRenderer.hpp"
#include "SimpleMenu.hpp"
#include "Game/State/MainMenuState.hpp"
#include "Game/State/PlayMenuState.hpp"
#include "Game/State/TerminateState.hpp"
#include "Game/State/PlayingState.hpp"
#include "Game/State/HoldState.hpp"
#include "Game/State/WinState.hpp"
#include "Game/State/LoseState.hpp"
#include "Game/State/SettingsState.hpp"
#include "Game/State/SizeChangeState.hpp"
#include "Game/State/DifficultyChangeState.hpp"
#include "GameRenderer.hpp"

static constexpr int32_t screen_width_ = 1366;
static constexpr int32_t screen_height_ = 768;
static const std::string root = "../../resources/";

static const std::vector<std::string> paths = {
	"menus/main_theme.png",
	"menus/play_menu.png",
	"menus/settings.png",
	"menus/win.png",
	"menus/lose.png"
};

SfmlRenderer::SfmlRenderer(SfmlInput &input) : window_(sf::VideoMode(screen_width_, screen_height_), "DungeonGame"), input_(input)
{
	// load textures
	load_data();
	// set up icon
	window_.setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
	// init sub renders
	init_slaves();
	// init input
	input.init_renderer(this);
}

void SfmlRenderer::load_data()
{
	if (!icon_.loadFromFile(root + "icon.png") || !font_.loadFromFile(root + "arial.ttf"))
	{
		destroy();
		throw std::invalid_argument(std::string("Failed to initialize resources"));
	}

	textures_.resize(paths.size());

	for (size_t i = 0; i < paths.size(); ++i)
	{
		if (!textures_[i].loadFromFile(root + paths[i]))
		{
			destroy();
			throw std::invalid_argument(std::string("Failed to initialize menu textures"));
		}
	}
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

void SfmlRenderer::init_slaves()
{
	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Play", input_.command("play")},
									  {"Settings", input_.command("options")},
									  {"Exit", input_.command("terminate")}},
									 textures_[MENU_TEXTURE::MAIN_MENU]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"New Game", input_.command("create")},
									  {"Back", input_.command("menu")}},
									 textures_[MENU_TEXTURE::PLAY_MENU]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Resume", input_.command("resume")},
									  {"Back", input_.command("menu")}},
									 textures_[MENU_TEXTURE::MAIN_MENU]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Restart", input_.command("restart")},
									  {"Menu", input_.command("menu")}},
									 textures_[MENU_TEXTURE::LOSE]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Next level", input_.command("create")},
									  {"Menu", input_.command("menu")}},
									 textures_[MENU_TEXTURE::WIN]));

	slaves_.push_back(new GameRenderer(window_,
									   font_,
									   input_));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Size", input_.command("size_state")},
									  {"Difficulty", input_.command("difficulty_state")},
									  {"Back", input_.command("menu")}},
									 textures_[MENU_TEXTURE::SETTINGS_MENU]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Small", input_.command("size_small")},
									  {"Medium", input_.command("size_medium")},
									  {"Big", input_.command("size_big")}},
									 textures_[MENU_TEXTURE::SETTINGS_MENU]));

	slaves_.push_back(new SimpleMenu(window_,
									 font_,
									 {{"Easy", input_.command("difficulty_easy")},
									  {"Medium", input_.command("difficulty_average")},
									  {"Hard", input_.command("difficulty_hard")}},
									 textures_[MENU_TEXTURE::SETTINGS_MENU]));

	suitable_for_state_[std::type_index(typeid(MainMenuState))] = 0;
	suitable_for_state_[std::type_index(typeid(PlayMenuState))] = 1;
	suitable_for_state_[std::type_index(typeid(HoldState))] = 2;
	suitable_for_state_[std::type_index(typeid(LoseState))] = 3;
	suitable_for_state_[std::type_index(typeid(WinState))] = 4;
	suitable_for_state_[std::type_index(typeid(PlayingState))] = 5;
	suitable_for_state_[std::type_index(typeid(SettingsState))] = 6;
	suitable_for_state_[std::type_index(typeid(SizeChangeState))] = 7;
	suitable_for_state_[std::type_index(typeid(DifficultyChangeState))] = 8;
}
