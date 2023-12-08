#pragma once

#include "IMessage.hpp"
#include "Logger/structures/PlayerStats.hpp"


class WinMessage : public IMessage
{
	PlayerInfo report_;
public:
	WinMessage(PlayerInfo info);
	std::string to_string() const override;
};
