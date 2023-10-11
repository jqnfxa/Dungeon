#include "MovePlayer.hpp"
#include "Game/Engine/GameEngine.hpp"

MovePlayer::MovePlayer() : MovePlayer(NONE)
{
}

MovePlayer::MovePlayer(DIRECTION direction) : direction_(direction)
{
}

void MovePlayer::execute(GameEngine &game)
{
	game.move_player(direction_, 1);
}

bool MovePlayer::operator==(Command *other)
{
	auto *ptr = dynamic_cast<MovePlayer *>(other);
	return compare(other) && ptr->direction_ == this->direction_;
}

bool MovePlayer::compare(Command *other) const
{
	return dynamic_cast<MovePlayer *>(other) != nullptr;
}

std::string MovePlayer::to_str() const
{
	return "Move player in " + std::to_string(direction_);
}
