#pragma once

#include "World/GameField.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"
#include "Input/Interface/InputClass.hpp"

enum STATE
{
	TERMINATE,
	MAIN_MENU,
	PLAY_MENU,
	SETTINGS,
	PLAYING,
	HOLD_MENU,
	DEATH_SCREEN,
	WIN_SCREEN
};

class GameEngine {
  STATE game_state_;
  MAP_SIZE size_;
  DIFFICULTY difficulty_;

  GameField *field_;
  GameField *field_initial_;

  Player *player_initial_;
  PlayerHandler *handler_;

  void clean_up();
  void set_state(STATE new_state);
 public:
  GameEngine();

  PlayerHandler *player();
  GameField *field();
  [[nodiscard]] STATE state() const;
  void goto_hold_menu();
  void goto_settings();

  void update(Input *input);

  void set_game_difficulty(DIFFICULTY difficulty);
  void set_game_size(MAP_SIZE size);

  bool player_win();
  bool player_lose();
  void create_session();
  void restart_session();
  void exit_to_menu();
  void exit_game();
};
