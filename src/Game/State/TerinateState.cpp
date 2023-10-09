#include "TerinateState.hpp"
#include "../../Command/System/TerminateProgram.hpp"

bool TerminateState::handle_command(GameEngine &game, Command *command)
{
	return false;
}
std::string TerminateState::to_str() const
{
	return "TerminateState";
}
