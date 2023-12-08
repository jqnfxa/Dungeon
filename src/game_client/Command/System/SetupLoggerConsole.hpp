#pragma once

#include "../ICommand.hpp"


class SetupLoggerConsole : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
