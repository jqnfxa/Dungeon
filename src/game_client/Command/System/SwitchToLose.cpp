#include "Engine/GameEngine.hpp"
#include "SwitchToLose.hpp"


void SwitchToLose::execute(GameEngine &engine)
{
	engine.switch_to_lose();
}
