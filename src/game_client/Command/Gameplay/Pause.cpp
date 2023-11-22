#include "Engine/GameEngine.hpp"
#include "Pause.hpp"


void Pause::execute(GameEngine &engine)
{
	engine.pause_game();
}
