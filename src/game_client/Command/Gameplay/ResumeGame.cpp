#include "ResumeGame.hpp"
#include "Engine/GameEngine.hpp"


void ResumeGame::execute(GameEngine &engine)
{
	engine.resume_game();
}
