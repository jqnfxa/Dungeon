#pragma once

#include "../ICommand.hpp"


class OpenPlayMenu : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
