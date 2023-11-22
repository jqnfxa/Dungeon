#pragma once

#include "../ICommand.hpp"


class ScrollUp : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
