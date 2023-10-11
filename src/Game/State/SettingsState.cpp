#include "SettingsState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/Gameplay/ChangeFieldSize.hpp"
#include "Command/Gameplay/ChangeGameDifficulty.hpp"

bool SettingsState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(ChangeFieldSize)
		|| typeid(*command) == typeid(ChangeGameDifficulty))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string SettingsState::to_str() const
{
	return "SettingsState";
}
