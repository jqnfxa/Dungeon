#pragma once

#include "../ICommand.hpp"


class ResumeGame : public ICommand
{
public:
	void execute(GameEngine &engine) override;
};
