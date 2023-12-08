#pragma once

#include "../ICommand.hpp"


class SetupLoggerBoth : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
