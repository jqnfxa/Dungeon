#pragma once

#include "../ICommand.hpp"


class ScrollDown : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
