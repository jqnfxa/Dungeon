#include "RestartSession.hpp"
#include "Game/GameEngine.hpp"

void RestartSession::execute(GameEngine &game)
{
	game.restart_session();
}

bool RestartSession::operator==(Command *other)
{
	return dynamic_cast<RestartSession *>(other) != nullptr;
}


