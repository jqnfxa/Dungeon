#pragma once

#include "Engine/GameObserver.hpp"
#include "IRender.hpp"


class Tracker : public GameObserver
{
	IRender *renderer_;
public:
	explicit Tracker(IRender *renderer);
	void update(const GameEngine &engine) override;
};
