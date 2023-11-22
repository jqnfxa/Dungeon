#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class Play : public IState
{
public:
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
