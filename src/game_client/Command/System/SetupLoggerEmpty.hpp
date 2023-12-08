#pragma once

#include "../ICommand.hpp"


class SetupLoggerEmpty : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
