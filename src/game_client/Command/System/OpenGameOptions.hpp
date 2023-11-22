#pragma once

#include "../ICommand.hpp"


class OpenGameOptions : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
