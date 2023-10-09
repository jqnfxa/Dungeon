#include "CreateSession.hpp"
#include "Game/Engine/GameEngine.hpp"

void CreateSession::execute(GameEngine &game)
{
	game.create_session();
}

bool CreateSession::operator==(Command *other)
{
	return dynamic_cast<CreateSession *>(other) != nullptr;
}
