#pragma once

#include "../ICommand.hpp"


class Select : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
