#pragma once

#include "IMessage.hpp"
#include "Command/ICommand.hpp"


class CommandHandledMessage : public IMessage
{
	ICommand *command_;
public:
	CommandHandledMessage(ICommand *command);
	std::string to_string() const override;
};
