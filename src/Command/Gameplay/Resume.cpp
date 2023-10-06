#include "Resume.hpp"
#include "Game/GameEngine.hpp"

void Resume::execute(GameEngine &game)
{
	game.resume();
}
bool Resume::operator==(Command *other)
{
	return dynamic_cast<Resume *>(other) != nullptr;
}
