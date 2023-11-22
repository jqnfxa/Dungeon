#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class Win : public IState
{
	Menu menu_;
public:
	Win();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
