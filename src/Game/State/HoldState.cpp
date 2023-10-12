#include "HoldState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenMainMenu.hpp"
#include "Command/Gameplay/ResumeGame.hpp"
#include "Command/Gameplay/RestartSession.hpp"

bool HoldState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(ResumeGame)
		|| typeid(*command) == typeid(RestartSession) || typeid(*command) == typeid(OpenMainMenu))
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
