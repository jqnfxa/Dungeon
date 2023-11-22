#pragma once

#include "../ICommand.hpp"


class Pause : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
