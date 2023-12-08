#include "WinMessage.hpp"
#include <sstream>


WinMessage::WinMessage(PlayerInfo info) : report_(info) {}

std::string WinMessage::to_string() const
{
	std::ostringstream oss;

	oss << "The player has won with following stats: \n" <<
	"Health: " << report_.health << '\n' <<
	"Armor: " << report_.armor << '\n' <<
	"Attack: " << report_.attack << '\n' <<
	"Defense: " << report_.defense << '\n' <<
	"Points: " << report_.points;

	return oss.str();
}
