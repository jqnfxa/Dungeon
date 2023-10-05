#include "GameState.hpp"

const std::string STATE_HI[] = {"TERMINATE",
								"MAIN_MENU",
								"PLAY_MENU",
								"SETTINGS",
								"PLAYING",
								"HOLD_MENU",
								"DEATH_SCREEN",
								"WIN_SCREEN"};

GameState::GameState() : GameState(MAIN_MENU)
{
}

GameState::GameState(GameState::STATE state) : state_(state)
{
}

void GameState::update(STATE new_state)
{
	state_ = new_state;
}
GameState::STATE GameState::active() const
{
	return state_;
}
std::string GameState::to_str() const
{
	return STATE_HI[state_];
}
bool GameState::operator==(GameState::STATE state)
{
	return state_ == state;
}
