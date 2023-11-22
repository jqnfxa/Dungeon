#include "ChangeDifficulty.hpp"
#include "Engine/GameEngine.hpp"


ChangeDifficulty::ChangeDifficulty(DIFFICULTY difficulty) : difficulty_(difficulty) {}

void ChangeDifficulty::execute(GameEngine &engine)
{
	engine.change_difficulty(difficulty_);
}
