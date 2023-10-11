#include "PlayingState.hpp"
#include "../../Command/Gameplay/MovePlayer.hpp"
#include "Game/Engine/GameEngine.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/OpenHoldMenu.hpp"

bool PlayingState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(MovePlayer)
		|| typeid(*command) == typeid(OpenHoldMenu))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string PlayingState::to_str() const
{
	return "PlayingState";
}
