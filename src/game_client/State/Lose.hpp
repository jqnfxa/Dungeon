#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class Lose : public IState
{
	Menu menu_;
public:
	Lose();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
