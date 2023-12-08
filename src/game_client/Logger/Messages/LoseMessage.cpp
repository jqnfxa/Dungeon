#include "LoseMessage.hpp"
#include <sstream>


LoseMessage::LoseMessage(const Position & dead_end) : report_(dead_end) {}

std::string LoseMessage::to_string() const
{
	std::ostringstream oss;

	oss << "Player died on the cell with coordinates: \n" <<
	"x: " << report_.x() << '\n' <<
	"y: " << report_.y();

	return oss.str();
}

