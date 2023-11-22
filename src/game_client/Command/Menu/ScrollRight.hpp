#pragma once

#include "../ICommand.hpp"


class ScrollRight : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
