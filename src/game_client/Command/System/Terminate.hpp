#pragma once

#include "../ICommand.hpp"


class Terminate : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
