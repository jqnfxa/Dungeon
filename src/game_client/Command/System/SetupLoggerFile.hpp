#pragma once

#include "../ICommand.hpp"


class SetupLoggerFile : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
