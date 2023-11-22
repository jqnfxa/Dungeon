#include "SFMLInput.hpp"


SFMLInput::SFMLInput(const std::string & config_path, sf::RenderWindow &window)
	: InputModel(config_path), window_(window) {}

void SFMLInput::update()
{
	ICommand *cmd = nullptr;

	sf::Event event{};
	if (window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				cmd = command("terminate");
				break;
			case sf::Event::KeyPressed:
				cmd = command(event.key.code);
				break;
			default:
				// we don't process other commands
				cmd = nullptr;
		}
	}

	if (cmd != nullptr)
	{
		notify_subscribers(cmd);
	}
}
