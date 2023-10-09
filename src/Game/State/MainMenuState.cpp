#include "MainMenuState.hpp"
#include "Command/System/GameOptions.hpp"
#include "Command/System/OpenPlayMenu.hpp"
#include "Command/System/TerminateProgram.hpp"

bool MainMenuState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;

	if (TerminateProgram().operator==(command) || GameOptions().operator==(command)
		|| OpenPlayMenu().operator==(command))
	{
		command->execute(game);
		is_handled = true;
	}

	return is_handled;
}
std::string MainMenuState::to_str() const
{
	return "MainMenuState";
}
