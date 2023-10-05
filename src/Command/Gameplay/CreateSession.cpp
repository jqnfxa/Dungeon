#include "CreateSession.hpp"
#include "Game/GameEngine.hpp"

void CreateSession::execute(GameEngine &game)
{
	game.goto_play_menu();
	game.create_session();
}

bool CreateSession::operator==(Command *other)
{
	return dynamic_cast<CreateSession *>(other) != nullptr;
}
