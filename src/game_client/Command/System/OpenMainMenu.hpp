#pragma once

#include "../ICommand.hpp"


class OpenMainMenu : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
