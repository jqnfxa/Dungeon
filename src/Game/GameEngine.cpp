#include "GameEngine.hpp"

GameEngine::GameEngine() : game_state_(MAIN_MENU),
						   size_(SMALL),
						   difficulty_(AVERAGE),
						   field_(nullptr),
						   field_initial_(nullptr),
						   player_initial_(nullptr),
						   handler_(nullptr)
{
}

PlayerHandler *GameEngine::player()
{
	return handler_;
}
GameField *GameEngine::field()
{
	return field_;
}

STATE GameEngine::state() const
{
	return game_state_;
}

void GameEngine::set_state(STATE new_state)
{
	game_state_ = new_state;
}

void GameEngine::goto_hold_menu()
{
	set_state(HOLD_MENU);
}

void GameEngine::goto_settings()
{
	set_state(SETTINGS);
}

void GameEngine::set_game_difficulty(DIFFICULTY difficulty)
{
	if (state() == PLAY_MENU)
	{
		difficulty_ = difficulty;
	}
}

void GameEngine::set_game_size(MAP_SIZE size)
{
	if (state() == PLAY_MENU)
	{
		size_ = size;
	}
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

	// which game_state should be?
	if (state() == PLAYING)
	{
		set_state(DEATH_SCREEN);
	}
}

bool GameEngine::player_win()
{
	if (state() != WIN_SCREEN)
	{
		if (handler_->get_position() == field_->exit_point() && handler_->is_alive())
		{
			set_state(WIN_SCREEN);
		}
	}
	return state() == WIN_SCREEN;
}
bool GameEngine::player_lose()
{
	if (state() != DEATH_SCREEN)
	{
		if (handler_->is_dead())
		{
			set_state(DEATH_SCREEN);
		}
	}
	return state() == DEATH_SCREEN;
}

void GameEngine::create_session()
{
	clean_up();

	DefaultLevelGenerator generator(size_, difficulty_);
	field_initial_ = generator.generate();
	player_initial_ = new Player;

	restart_session();
}

void GameEngine::restart_session()
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
	handler_->set_position(field_->start_point());

	set_state(PLAYING);
}

void GameEngine::exit_to_menu()
{
	clean_up();
	set_state(MAIN_MENU);
}

void GameEngine::exit_game()
{
	clean_up();
	set_state(TERMINATE);
}

void GameEngine::update(Input *input)
{
	input->command()->execute(*this);

	if (state() == PLAYING)
	{
		if (player_lose())
		{
			set_state(DEATH_SCREEN);
		}
		else if (player_win())
		{
			set_state(WIN_SCREEN);
		}
		else
		{
			// game continue
			// move bots section
		}
	}
}