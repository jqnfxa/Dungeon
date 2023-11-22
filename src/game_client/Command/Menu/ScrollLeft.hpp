#pragma once

#include "../ICommand.hpp"


class ScrollLeft : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
