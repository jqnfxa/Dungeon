#include "WinState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenMainMenu.hpp"
#include "Command/Gameplay/CreateSession.hpp"

bool WinState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (TerminateProgram().operator==(command) || CreateSession().operator==(command)
		|| OpenMainMenu().operator==(command))
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
