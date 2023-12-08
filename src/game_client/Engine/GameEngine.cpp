#include "GameEngine.hpp"
#include "Path.hpp"
#include "State/Defines.hpp"
#include "Logger/structures/PlayerStats.hpp"
#include "Logger/Messages/CommandHandledMessage.hpp"
#include "Logger/Messages/CommandUnhandledMessage.hpp"
#include "Logger/Messages/LoseMessage.hpp"
#include "Logger/Messages/WinMessage.hpp"
#include "Logger/Messages/NewGameMessage.hpp"
#include "Logger/Printers/ConsolePrinter.hpp"
#include "Logger/Printers/FilePrinter.hpp"
#include "Logger/MessageBus.hpp"
#include <iostream>


GameEngine::GameEngine(MessageBus &logger)
	: game_state_(new MainMenuState)
	, size_(MAP_SIZE::SMALL)
	, difficulty_(DIFFICULTY::EASY)
	, field_initial_(nullptr)
	, field_current_(nullptr)
	, handler_initial_(nullptr)
	, handler_current_(nullptr)
	, logger_(logger)
{
	setup_logger_empty();
}

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

		if (status == true)
		{
			logger_.send_message(new CommandHandledMessage(cmd));
		}
		else
		{
			logger_.send_message(new CommandUnhandledMessage);
		}

	}

	if (is_playing())
	{
		if (is_win())
		{
			PlayerInfo report;
			report.health = player()->get_health();
			report.armor = player()->get_armor();
			report.attack = player()->get_attack();
			report.defense = player()->get_defense();
			report.points = player()->get_points();

			logger_.send_message(new WinMessage(report));
			switch_to_win();
		}
		else if (is_lose())
		{
			logger_.send_message(new LoseMessage(player()->get_position()));
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

	logger_.send_message(new NewGameMessage(field_initial_->dimensions(), field_initial_->start_point()));

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

void GameEngine::setup_logger_empty()
{
	logger_.reset_printers();
}

void GameEngine::setup_logger_console()
{
	setup_logger_empty();
	logger_.set_printer(new ConsolePrinter);
}

void GameEngine::setup_logger_file()
{
	setup_logger_empty();
	logger_.set_printer(new FilePrinter(game_dir + "/log"));
}

void GameEngine::setup_logger_both()
{
	setup_logger_empty();
	logger_.set_printer(new ConsolePrinter);
	logger_.set_printer(new FilePrinter(game_dir + "/log"));
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
