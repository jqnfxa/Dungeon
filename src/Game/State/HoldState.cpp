#include "HoldState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/Gameplay/ResumeGame.hpp"
#include "Command/System/OpenMainMenu.hpp"

bool HoldState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (TerminateProgram().operator==(command) || ResumeGame().operator==(command)
		|| OpenMainMenu().operator==(command))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string HoldState::to_str() const
{
	return "HoldState";
}
