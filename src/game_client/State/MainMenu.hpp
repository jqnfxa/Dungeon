#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class MainMenuState : public IState
{
	Menu menu_;
public:
	MainMenuState();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
