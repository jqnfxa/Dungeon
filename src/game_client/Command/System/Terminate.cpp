#include "Engine/GameEngine.hpp"
#include "Terminate.hpp"


void Terminate::execute(GameEngine &engine)
{
	engine.terminate_game();
}
