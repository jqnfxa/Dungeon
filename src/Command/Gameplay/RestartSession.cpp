#include "RestartSession.hpp"
#include "Game/Engine/GameEngine.hpp"

void RestartSession::execute(GameEngine &game)
{
	game.restart_session();
}

bool RestartSession::operator==(Command *other)
{
	return dynamic_cast<RestartSession *>(other) != nullptr;
}

std::string RestartSession::to_str() const
{
	return "RestartSession";
}


