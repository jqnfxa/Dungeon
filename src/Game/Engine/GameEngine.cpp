#include "GameEngine.hpp"
#include "Game/State/TerminateState.hpp"
#include "Game/State/SettingsState.hpp"
#include "Game/State/MainMenuState.hpp"
#include "Game/State/PlayMenuState.hpp"
#include "Game/State/PlayingState.hpp"
#include "Game/State/HoldState.hpp"
#include <iostream>

GameEngine::GameEngine() : current_state_(new MainMenuState),
						   size_(SMALL),
						   difficulty_(EASY),
						   field_(nullptr),
						   field_initial_(nullptr),
						   player_initial_(nullptr),
						   handler_(nullptr)
{
}

GameEngine::~GameEngine()
{
	release_resources();
	delete current_state_;
	current_state_ = nullptr;
	observers_.clear();
}

void GameEngine::release_resources()
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

void GameEngine::update(Command *command)
{
	notify_observers();

	if (command == nullptr)
	{
		return;
	}

	bool result = current_state_->handle_command(*this, command);

	// handle command execution
	if (result)
	{
		std::cerr << "Successfully executed: " << command->to_str() << '\n';
	}
	else
	{
		std::cerr << "Command not handled: " << command->to_str() << '\n';
	}

	notify_observers();
}

void GameEngine::set_state(GameState *state)
{
	delete current_state_;
	current_state_ = state;

	// notify subscribers
}

GameState *GameEngine::state() const
{
	return current_state_;
}

void GameEngine::move_player(DIRECTION direction, int32_t power)
{
	handler_->move_by_direction(direction, power);
}

void GameEngine::exit_game()
{
	release_resources();
	set_state(new TerminateState);
}

void GameEngine::open_settings()
{
	set_state(new SettingsState);
}

void GameEngine::open_main_menu()
{
	set_state(new MainMenuState);
}

void GameEngine::open_play_menu()
{
	set_state(new PlayMenuState);
}

void GameEngine::open_hold_menu()
{
	set_state(new HoldState);
}

void GameEngine::create_session()
{
	release_resources();

	DefaultLevelGenerator generator(size_, difficulty_);
	field_initial_ = generator.generate();
	player_initial_ = new Player;

	restart_session();
}

void GameEngine::restart_session()
{
	delete field_;
	field_ = new GameField(*field_initial_);
	delete handler_;
	handler_ = new PlayerHandler(new Player(*player_initial_));
	handler_->register_observer(field_);
	handler_->set_position(field_->start_point());

	set_state(new PlayingState);
}

void GameEngine::resize_filed(MAP_SIZE new_size)
{
	size_ = new_size;
}

void GameEngine::change_difficulty(DIFFICULTY new_difficulty)
{
	difficulty_ = new_difficulty;
}

void GameEngine::resume()
{
	if (!field_initial_)
	{
		create_session();
	}
	else
	{
		set_state(new PlayingState);
	}
}

PlayerHandler *GameEngine::player() const
{
	return handler_;
}

GameField *GameEngine::field() const
{
	return field_;
}

void GameEngine::add_observer(GameObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	observers_.push_back(observer);
}

void GameEngine::remove_observer(GameObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	auto it = std::find(observers_.begin(), observers_.end(), observer);

	if (it != observers_.end())
	{
		observers_.erase(it);
	}
}

void GameEngine::notify_observers()
{
	for (auto &observer : observers_)
	{
		observer->update(*this);
	}
}
