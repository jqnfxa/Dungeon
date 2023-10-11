#include "PlayMenuState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/Gameplay/CreateSession.hpp"
#include "Command/System/OpenMainMenu.hpp"

bool PlayMenuState::handle_command(GameEngine &game, Command *command)
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
std::string PlayMenuState::to_str() const
{
	return "PlayMenuState";
}
