#include "TerminateProgram.hpp"
#include "Game/GameEngine.hpp"

void TerminateProgram::execute(GameEngine &game)
{
	game.exit_game();
}
bool TerminateProgram::operator==(Command *other)
{
	return dynamic_cast<TerminateProgram *>(other) != nullptr;
}
