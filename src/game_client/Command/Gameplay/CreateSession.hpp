#pragma once

#include "../ICommand.hpp"


class CreateSession : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
