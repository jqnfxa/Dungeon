#include "NewGameMessage.hpp"
#include <sstream>


NewGameMessage::NewGameMessage(const Dimension &dimension, const Position &position)
	: dimension_(dimension)
	, position_(position) {}

std::string NewGameMessage::to_string() const
{
	std::ostringstream oss;

	oss << "New game was started.\n" <<
	"Map dimensions: " << dimension_.x() << ", " << dimension_.y() << '\n' <<
	"Start position: " << position_.x() << ", " << position_.y();

	return oss.str();
}

