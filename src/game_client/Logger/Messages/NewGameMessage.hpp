#pragma once

#include "IMessage.hpp"
#include "Movement/Aliases.hpp"


class NewGameMessage : public IMessage
{
	Dimension dimension_;
	Position position_;
public:
	NewGameMessage(const Dimension &dimension, const Position &position);
	std::string to_string() const override;
};
