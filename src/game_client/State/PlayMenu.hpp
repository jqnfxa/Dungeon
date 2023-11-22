#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class PlayMenu : public IState
{
	Menu menu_;
public:
	PlayMenu();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
