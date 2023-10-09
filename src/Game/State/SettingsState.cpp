#include "SettingsState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/Gameplay/ChangeFieldSize.hpp"
#include "Command/Gameplay/ChangeGameDifficulty.hpp"

bool SettingsState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (TerminateProgram().operator==(command) || ChangeFieldSize().operator==(command)
		|| ChangeGameDifficulty().operator==(command))
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
