#include "ChangeSize.hpp"
#include "Engine/GameEngine.hpp"


ChangeSize::ChangeSize(MAP_SIZE size) : size_(size) {}

void ChangeSize::execute(GameEngine &engine)
{
	engine.change_size(size_);
}
