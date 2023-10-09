#pragma once

#include "World/GameField.hpp"
#include "Handlers/PlayerHandler/PlayerHandler.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"
#include "Game/State/GameState.hpp"

class GameEngine {
  GameState *current_state_;

  // game field attributes
  MAP_SIZE size_;
  DIFFICULTY difficulty_;
  GameField *field_;
  GameField *field_initial_;

  // player attributes
  Player *player_initial_;
  PlayerHandler *handler_;

  void release_resources();
 public:
  GameEngine();
  ~GameEngine();

  void update(Command *command);

  // game state changers
  void set_state(GameState *state);
  GameState *state();

  void exit_game();
  void move_player(DIRECTION direction, int32_t power);
  void open_settings();
  void open_main_menu();
  void open_play_menu();
  void open_hold_menu();
  void create_session();
  void restart_session();
  void resize_filed(MAP_SIZE new_size);
  void change_difficulty(DIFFICULTY new_difficulty);
  void resume();

  [[nodiscard]] PlayerHandler *player() const;
  [[nodiscard]] GameField *field() const;
};
