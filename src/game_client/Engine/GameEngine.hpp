#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "World/GameField.hpp"
#include "Movement/Direction.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"
#include "State/IState.hpp"
#include "Command/ICommand.hpp"
#include "Input/InputObserver.hpp"
#include "GameObserver.hpp"
#include "Logger/MessageBus.hpp"


class GameEngine : public InputObserver
{
	IState *game_state_;

	MAP_SIZE size_;
	DIFFICULTY difficulty_;

	GameField *field_initial_;
	GameField *field_current_;

	PlayerHandler *handler_initial_;
	PlayerHandler *handler_current_;

	std::queue<ICommand *> command_queue_;
	std::vector<GameObserver *> observers_;

	MessageBus &logger_;

	void clean_up();
public:
	GameEngine(MessageBus &logger);
	~GameEngine();

	[[nodiscard]] bool is_running() const;
	[[nodiscard]] bool is_playing() const;
	[[nodiscard]] bool is_win() const;
	[[nodiscard]] bool is_lose() const;

	void update(ICommand *command) override;
	void update();

	void set_state(IState *new_state);
	IState *get_state() const;

	PlayerHandler *player() const;
	GameField *field() const;

	void create_session();
	void restart_session();
	void move_player(DIRECTION direction, int32_t force);
	void pause_game();
	void resume_game();
	void change_difficulty(DIFFICULTY difficulty);
	void change_size(MAP_SIZE size);

	void setup_logger_empty();
	void setup_logger_console();
	void setup_logger_file();
	void setup_logger_both();

	void open_game_options();
	void open_main_menu();
	void open_play_menu();
	void switch_to_lose();
	void switch_to_win();
	void terminate_game();

	void scroll_up();
	void scroll_down();
	void scroll_left();
	void scroll_right();
	void select();

	void add_observer(GameObserver *observer);
	void notify_observers();
	void remove_observer(GameObserver *observer);
};
