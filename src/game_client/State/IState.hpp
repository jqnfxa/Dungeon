#pragma once

#include "Command/ICommand.hpp"
#include "../MenuObject/Menu.hpp"


class GameEngine;
class IState
{
public:
	virtual ~IState() = default;
	virtual Menu *menu() = 0;
	[[nodiscard]] virtual bool handle_command(GameEngine &engine, ICommand* command) = 0;
};
