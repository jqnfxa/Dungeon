#pragma once

#include "../ICommand.hpp"


class SwitchToWin : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
