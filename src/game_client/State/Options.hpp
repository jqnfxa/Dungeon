#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"


class Options : public IState
{
	Menu menu_;
public:
	Options();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
