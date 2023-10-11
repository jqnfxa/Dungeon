#include "WinState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenMainMenu.hpp"
#include "Command/Gameplay/CreateSession.hpp"

bool WinState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(CreateSession)
		|| typeid(*command) == typeid(OpenMainMenu))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string WinState::to_str() const
{
	return "WinState";
}
