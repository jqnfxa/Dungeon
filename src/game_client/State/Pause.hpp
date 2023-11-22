#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class HoldState : public IState
{
	Menu menu_;
public:
	HoldState();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
