#include "MovePlayer.hpp"
#include "Game/GameEngine.hpp"

MovePlayer::MovePlayer(DIRECTION direction) : direction_(direction)
{
}

void MovePlayer::execute(GameEngine &game)
{
	game.player()->move_by_direction(direction_, 1);

	// TODO set direction to NONE to avoid class abuse?
}
bool MovePlayer::operator==(Command *other)
{
	auto *ptr = dynamic_cast<MovePlayer *>(other);
	return ptr != nullptr && ptr->direction_ == this->direction_;
}
