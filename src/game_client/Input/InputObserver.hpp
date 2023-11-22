#pragma once

#include "Command/ICommand.hpp"


class InputObserver
{
public:
	virtual ~InputObserver() = default;
	virtual void update(ICommand *command) = 0;
};
