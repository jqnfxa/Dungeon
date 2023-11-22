#include "Terminate.hpp"
#include "Command/Defines.hpp"


Menu *TerminateState::menu()
{
	return nullptr;
}

bool TerminateState::handle_command(GameEngine &engine, ICommand *command)
{
	return false;
}
