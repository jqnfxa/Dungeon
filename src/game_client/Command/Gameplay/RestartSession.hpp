#pragma once

#include "../ICommand.hpp"


class RestartSession : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
