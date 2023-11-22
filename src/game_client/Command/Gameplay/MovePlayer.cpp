#include "MovePlayer.hpp"
#include "Engine/GameEngine.hpp"


MovePlayer::MovePlayer(DIRECTION direction) : direction_(direction) {}

void MovePlayer::execute(GameEngine &engine)
{
	engine.move_player(direction_, 1);
}
