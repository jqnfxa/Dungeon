#include "Engine/GameEngine.hpp"
#include "SwitchToWin.hpp"


void SwitchToWin::execute(GameEngine &engine)
{
	engine.switch_to_win();
}
