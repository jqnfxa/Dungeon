#include "SFMLInput.hpp"
#include "Logger/Messages/KeyPressedMessage.hpp"
#include "Logger/MessageBus.hpp"


SFMLInput::SFMLInput(const std::string & config_path, sf::RenderWindow &window, MessageBus &logger)
	: InputModel(config_path)
	, window_(window)
	, logger_(logger) {}

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
				logger_.send_message(new KeyPressedMessage(event.key.code));
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
