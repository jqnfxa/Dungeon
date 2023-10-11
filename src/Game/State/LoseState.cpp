#include "LoseState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenMainMenu.hpp"
#include "Command/Gameplay/RestartSession.hpp"

bool LoseState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram)
		|| typeid(*command) == typeid(RestartSession)
		|| typeid(*command) == typeid(OpenMainMenu))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string LoseState::to_str() const
{
	return "LoseState";
}
