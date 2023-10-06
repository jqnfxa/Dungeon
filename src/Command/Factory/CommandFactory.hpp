#pragma once

#include <unordered_map>
#include "Command/Interface/Interface.hpp"

enum COMMAND
{
	CREATE_SESSION,
	RESTART_SESSION,
	RESUME,
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_UP,
	MOVE_DOWN,
	OPEN_SETTINGS,
	OPEN_HOLD_MENU,
	OPEN_PLAY_MENU,
	RETURN_TO_MENU,
	TERMINATE,
	EMPTY_OPERATION
};

class CommandFactory {
  std::unordered_map<COMMAND, Command *> translate_;

  CommandFactory();
 public:
  CommandFactory(const CommandFactory &other) = delete;
  CommandFactory &operator=(const CommandFactory &other) = delete;
  ~CommandFactory();

  static CommandFactory &instance()
  {
	  static CommandFactory instance_;
	  return instance_;
  }

  Command *create(COMMAND command) const;
};
