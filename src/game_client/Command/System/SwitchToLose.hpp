#pragma once

#include "../ICommand.hpp"


class SwitchToLose : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
