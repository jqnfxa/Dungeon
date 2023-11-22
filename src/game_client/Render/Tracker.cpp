#include "Tracker.hpp"
#include "Engine/GameEngine.hpp"


Tracker::Tracker(IRender *renderer) : renderer_(renderer)
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
