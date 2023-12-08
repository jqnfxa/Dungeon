#pragma once

#include "IMessage.hpp"


class CommandUnhandledMessage : public IMessage
{
public:
	std::string to_string() const override;
};
