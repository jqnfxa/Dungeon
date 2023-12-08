#pragma once

#include "IMessage.hpp"


class KeyPressedMessage : public IMessage
{
	int key_code_;
public:
	KeyPressedMessage(int key_code);
	std::string to_string() const override;
};
