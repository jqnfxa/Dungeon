#include "NOP.hpp"

void NOP::execute(GameEngine &game)
{
	// do nothing
}
bool NOP::operator==(Command *other)
{
	return dynamic_cast<NOP *>(other) != nullptr;
}
