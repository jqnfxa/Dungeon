#include "TerminateState.hpp"
#include "../../Command/System/TerminateProgram.hpp"

bool TerminateState::handle_command(GameEngine &game, Command *command)
{
	// this state should not handle any command because game will be deleted anyway
	return false;
}

std::string TerminateState::to_str() const
{
	return "TerminateState";
}
