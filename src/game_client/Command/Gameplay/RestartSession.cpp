#include "RestartSession.hpp"
#include "Engine/GameEngine.hpp"


void RestartSession::execute(GameEngine &engine)
{
	engine.restart_session();
}
