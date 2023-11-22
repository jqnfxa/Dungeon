#include "CreateSession.hpp"
#include "Engine/GameEngine.hpp"


void CreateSession::execute(GameEngine &engine)
{
	engine.create_session();
}
