#pragma once

#include "IMessage.hpp"
#include "Movement/Aliases.hpp"


class LoseMessage : public IMessage
{
	Position report_;
public:
	LoseMessage(const Position& dead_end);
	std::string to_string() const override;
};
