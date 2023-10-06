#include "CommandFactory.hpp"
#include "Command/Gameplay/ChangeGameDifficulty.hpp"
#include "Command/Gameplay/CreateSession.hpp"
#include "Command/Gameplay/RestartSession.hpp"
#include "Command/Gameplay/Resume.hpp"
#include "Command/Gameplay/MovePlayer.hpp"
#include "Command/System/GoToSettings.hpp"
#include "Command/System/TriggerHoldMenu.hpp"
#include "Command/System/TriggerPlayMenu.hpp"
#include "Command/System/ReturnToMenu.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/NOP.hpp"

CommandFactory::CommandFactory()
{
	translate_[CREATE_SESSION] = new CreateSession;
	translate_[RESTART_SESSION] = new RestartSession;
	translate_[RESUME] = new Resume;
	translate_[MOVE_RIGHT] = new MovePlayer(DIRECTION::RIGHT);
	translate_[MOVE_LEFT] = new MovePlayer(DIRECTION::LEFT);
	translate_[MOVE_UP] = new MovePlayer(DIRECTION::UP);
	translate_[MOVE_DOWN] = new MovePlayer(DIRECTION::DOWN);
	translate_[OPEN_SETTINGS] = new GoToSettings;
	translate_[OPEN_HOLD_MENU] = new TriggerHoldMenu;
	translate_[OPEN_PLAY_MENU] = new TriggerPlayMenu;
	translate_[RETURN_TO_MENU] = new ReturnToMenu;
	translate_[TERMINATE] = new TerminateProgram;
	translate_[EMPTY_OPERATION] = new NOP;
}

CommandFactory::~CommandFactory()
{
	for (auto &[key, value] : translate_)
	{
		delete value;
	}
	translate_.clear();
}
Command *CommandFactory::create(COMMAND command) const
{
	return translate_.at(command);
}