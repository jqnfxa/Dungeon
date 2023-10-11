#include "TerminateProgram.hpp"
#include "Game/Engine/GameEngine.hpp"

void TerminateProgram::execute(GameEngine &game)
{
	game.exit_game();
}

bool TerminateProgram::operator==(Command *other)
{
	return dynamic_cast<TerminateProgram *>(other) != nullptr;
}

std::string TerminateProgram::to_str() const
{
	return "TerminateProgram";
}
