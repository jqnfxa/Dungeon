#include "SettingsState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenMainMenu.hpp"
#include "Command/System/OpenSizeOptions.hpp"
#include "Command/System/OpenDifficultyOptions.hpp"
#include "Command/Gameplay/ChangeFieldSize.hpp"

bool SettingsState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(OpenSizeOptions)
		|| typeid(*command) == typeid(OpenDifficultyOptions) || typeid(*command) == typeid(OpenMainMenu))
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
