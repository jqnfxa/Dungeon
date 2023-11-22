#include "ScrollLeft.hpp"
#include "Engine/GameEngine.hpp"


void ScrollLeft::execute(GameEngine &engine)
{
	engine.scroll_left();
}
