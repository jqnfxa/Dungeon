#include "Tracker.hpp"
#include "Game/Engine/GameEngine.hpp"

Tracker::Tracker(Renderer *renderer) : renderer_(renderer)
{
	if (renderer_ == nullptr)
	{
		throw std::invalid_argument("Invalid render object");
	}
}

void Tracker::update(const GameEngine &engine)
{
	renderer_->render(engine);
}