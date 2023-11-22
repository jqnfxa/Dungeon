#include "GameEngine.hpp"
#include "State/Defines.hpp"
#include <iostream>

GameEngine::GameEngine()
	: game_state_(new MainMenuState),
	size_(MAP_SIZE::SMALL),
	difficulty_(DIFFICULTY::EASY),
	field_initial_(nullptr),
	field_current_(nullptr),
	handler_initial_(nullptr),
	handler_current_(nullptr) {}

GameEngine::~GameEngine()
{
	delete game_state_;
	delete field_initial_;
	delete field_current_;
	delete handler_initial_;
	delete handler_current_;
}

bool GameEngine::is_running() const
{
	return game_state_ != nullptr && typeid(*game_state_) != typeid(TerminateState);
}

bool GameEngine::is_playing() const
{
	return game_state_ != nullptr && typeid(*game_state_) == typeid(Play);
}

bool GameEngine::is_win() const
{
	return handler_current_ && handler_current_->get_health() >= 0 && handler_current_->get_position() == field_current_->exit_point();
}

bool GameEngine::is_lose() const
{
	return handler_current_ && handler_current_->get_health() == 0;
}

void GameEngine::update(ICommand *command)
{
	command_queue_.push(command);
}

void GameEngine::update()
{
	while (!command_queue_.empty())
	{
		auto *cmd = command_queue_.front();
		command_queue_.pop();

		auto status = game_state_->handle_command(*this, cmd);
	}

	if (is_playing())
	{
		if (is_win())
		{
			switch_to_win();
		}
		else if (is_lose())
		{
			switch_to_lose();
		}

		// entity game loop

	}

	notify_observers();
}

void GameEngine::set_state(IState *new_state)
{
	delete game_state_;
	game_state_ = new_state;
}

IState *GameEngine::get_state() const
{
	return game_state_;
}

PlayerHandler *GameEngine::player() const
{
	return handler_current_;
}

GameField * GameEngine::field() const
{
	return field_current_;
}

void GameEngine::create_session()
{
	delete field_initial_;
	delete handler_initial_;

	DefaultLevelGenerator generator(size_, difficulty_);
	field_initial_ = generator.generate();
	handler_initial_ = new PlayerHandler(new Player);

	restart_session();
}

void GameEngine::restart_session()
{
	delete field_current_;
	delete handler_current_;

	field_current_ = new GameField(*field_initial_);
	handler_current_ = new PlayerHandler(new Player);

	handler_current_->register_observer(field_current_);
	handler_current_->set_position(field_current_->start_point());

	set_state(new Play);
}

void GameEngine::move_player(DIRECTION direction, int32_t force)
{
	handler_current_->move_by_direction(direction, force);
}

void GameEngine::pause_game()
{
	set_state(new HoldState);
}

void GameEngine::resume_game()
{
	set_state(new Play);
}

void GameEngine::change_difficulty(DIFFICULTY difficulty)
{
	difficulty_ = difficulty;
}

void GameEngine::change_size(MAP_SIZE size)
{
	size_ = size;
}

void GameEngine::open_game_options()
{
	set_state(new Options);
}

void GameEngine::open_main_menu()
{
	set_state(new MainMenuState);
}

void GameEngine::open_play_menu()
{
	set_state(new PlayMenu);
}

void GameEngine::switch_to_lose()
{
	set_state(new Lose);
}

void GameEngine::switch_to_win()
{
	set_state(new Win);
}

void GameEngine::terminate_game()
{
	set_state(new TerminateState);
}

void GameEngine::scroll_up()
{
	if (game_state_->menu() != nullptr)
	{
		game_state_->menu()->scroll_up();
	}
}

void GameEngine::scroll_down()
{
	if (game_state_->menu() != nullptr)
	{
		game_state_->menu()->scroll_down();
	}
}

void GameEngine::scroll_left()
{
	if (game_state_->menu() != nullptr)
	{
		game_state_->menu()->scroll_left();
	}
}

void GameEngine::scroll_right()
{
	if (game_state_->menu() != nullptr)
	{
		game_state_->menu()->scroll_right();
	}
}

void GameEngine::select()
{
	if (game_state_->menu() != nullptr)
	{
		auto status = game_state_->handle_command(*this, game_state_->menu()->select());
	}
}

void GameEngine::add_observer(GameObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	observers_.push_back(observer);
}

void GameEngine::notify_observers()
{
	for(auto &observer : observers_)
	{
		observer->update(*this);
	}
}

void GameEngine::remove_observer(GameObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}
