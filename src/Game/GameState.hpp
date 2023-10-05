#pragma once

#include <string>

class GameState {
 public:
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
 public:
  GameState();
  explicit GameState(STATE state);
  void update(STATE new_state);
  [[nodiscard]] STATE active() const;
  [[nodiscard]] std::string to_str() const;
  [[nodiscard]] bool operator==(STATE state);
 private:
  STATE state_;
};
