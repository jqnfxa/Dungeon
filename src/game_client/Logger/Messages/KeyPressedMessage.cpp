#include "KeyPressedMessage.hpp"
#include <sstream>


KeyPressedMessage::KeyPressedMessage(int key_code) : key_code_(key_code) {}

std::string KeyPressedMessage::to_string() const
{
	std::ostringstream oss;

	oss << "Pressed key with code: " << key_code_;

	return oss.str();
}


