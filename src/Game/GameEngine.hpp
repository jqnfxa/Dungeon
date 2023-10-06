#pragma once

#include "World/GameField.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"
#include "Input/Interface/InputClass.hpp"
#include "GameState.hpp"

class GameEngine {
  GameState game_state_;
  MAP_SIZE size_;
  DIFFICULTY difficulty_;

  GameField *field_;
  GameField *field_initial_;

  Player *player_initial_;
  PlayerHandler *handler_;

  void clean_up();
  void set_state(GameState::STATE new_state);
  void play_menu_requirements() const;
  void reset_game();

  // private game states changers
  void goto_win_screen();
  void goto_death_screen();
 public:
  GameEngine();
  ~GameEngine();

  // game state getters
  PlayerHandler *player();
  GameField *field();
  [[nodiscard]] GameState state() const;

  // game states changers
  void goto_hold_menu();
  void resume();
  void goto_play_menu();
  void goto_settings();
  void exit_to_menu();
  void exit_game();

  // available only in PLAY_MENU
  void set_game_difficulty(DIFFICULTY difficulty);
  void set_game_size(MAP_SIZE size);
  void create_session();

  // available when playing (PLAYING | HOLD_MENU)
  // prefer HOLD_MENU only
  void restart_session();

  // should be private methods
  bool player_win();
  bool player_lose();

  // function to update inner game state
  void update(Command *command);
};
