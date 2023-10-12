#include "SfmlInput.hpp"
#include "../../Draw/SFML/SfmlRenderer.hpp"

SfmlInput::SfmlInput(const std::string &config_path) : Input(config_path), renderer_(nullptr)
{
}

void SfmlInput::init_renderer(SfmlRenderer *renderer)
{
	renderer_ = renderer;
}

void SfmlInput::update(GameState *game_state)
{
	if (renderer_ == nullptr)
	{
		throw std::invalid_argument("SfmlRender was not inited");
	}

	last_command_ = renderer_->retrieve_input(game_state);
}

