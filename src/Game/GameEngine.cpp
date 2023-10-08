#include "GameEngine.hpp"
#include <sstream>

GameEngine::GameEngine() : game_state_(GameState::MAIN_MENU),
						   size_(SMALL),
						   difficulty_(AVERAGE),
						   field_(nullptr),
						   field_initial_(nullptr),
						   player_initial_(nullptr),
						   handler_(nullptr)
{
}

GameEngine::~GameEngine()
{
	clean_up();
	game_state_.update(GameState::MAIN_MENU);
}

PlayerHandler *GameEngine::player()
{
	return handler_;
}
GameField *GameEngine::field()
{
	return field_;
}

GameState GameEngine::state() const
{
	return game_state_;
}

void GameEngine::set_state(GameState::STATE new_state)
{
	game_state_.update(new_state);
}

void GameEngine::open_hold_menu()
{
	set_state(GameState::HOLD_MENU);
}

void GameEngine::open_play_menu()
{
	set_state(GameState::PLAY_MENU);
}

void GameEngine::open_settings()
{
	set_state(GameState::SETTINGS);
}

void GameEngine::resume()
{
	if (state() == GameState::HOLD_MENU)
	{
		set_state(GameState::PLAYING);
	}
}

void GameEngine::exit_to_menu()
{
	clean_up();
	set_state(GameState::MAIN_MENU);
}

void GameEngine::exit_game()
{
	clean_up();
	set_state(GameState::TERMINATE);
}

void GameEngine::goto_win_screen()
{
	set_state(GameState::WIN_SCREEN);
}

void GameEngine::goto_death_screen()
{
	set_state(GameState::DEATH_SCREEN);
}

void GameEngine::set_game_difficulty(DIFFICULTY difficulty)
{
	requirements(GameState(GameState::SETTINGS));
	difficulty_ = difficulty;
}

void GameEngine::set_game_size(MAP_SIZE size)
{
	requirements(GameState(GameState::SETTINGS));
	size_ = size;
}

void GameEngine::clean_up()
{
	delete field_initial_;
	field_initial_ = nullptr;
	delete field_;
	field_ = nullptr;

	delete player_initial_;
	player_initial_ = nullptr;
	delete handler_;
	handler_ = nullptr;
}

bool GameEngine::player_win()
{
	if (state() != GameState::WIN_SCREEN)
	{
		if (handler_->get_position() == field_->exit_point() && handler_->is_alive())
		{
			set_state(GameState::WIN_SCREEN);
		}
	}
	return state() == GameState::WIN_SCREEN;
}

bool GameEngine::player_lose()
{
	if (state() != GameState::DEATH_SCREEN)
	{
		if (handler_->is_dead())
		{
			set_state(GameState::DEATH_SCREEN);
		}
	}
	return state() == GameState::DEATH_SCREEN;
}

void GameEngine::create_session()
{
	// requirements will be settings
	// (because game should be created after init game size and difficulty)
	// requirements(GameState(GameState::SETTINGS));
	clean_up();

	DefaultLevelGenerator generator(size_, difficulty_);
	field_initial_ = generator.generate();
	player_initial_ = new Player;

	reset_game();
}

void GameEngine::restart_session()
{
	// requirements later
	// requirements(GameState(GameState::HOLD_MENU));
	reset_game();
}

void GameEngine::update(Command *command)
{
	if (command != nullptr)
	{
		command->execute(*this);

		if (state() == GameState::PLAYING)
		{
			if (player_win())
			{
				goto_win_screen();
			}
			else if (player_lose())
			{
				goto_death_screen();
			}
			else
			{
				// game continue
				// move bots section
			}
		}
	}
}

void GameEngine::reset_game()
{
	if (field_ == nullptr)
	{
		field_ = new GameField;
	}
	// reset map
	*field_ = *field_initial_;

	// reset player
	delete handler_;
	handler_ = new PlayerHandler(new Player(*player_initial_));
	handler_->register_observer(field_);
	handler_->set_position(field_->start_point());

	set_state(GameState::PLAYING);
}
void GameEngine::requirements(GameState needle) const
{
	if (state() != needle.active())
	{
		std::stringstream ss;
		ss << "Unexpected state: " << state().to_str() << " expected: " << needle.to_str();
		throw std::invalid_argument(ss.str());
	}
}