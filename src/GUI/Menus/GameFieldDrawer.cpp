#include "GameFieldDrawer.hpp"
#include "Command/Factory/CommandFactory.hpp"

GameFieldDrawer::GameFieldDrawer(Window &parent) : window_(parent)
{
}

Command *GameFieldDrawer::on_key_press(const sf::Event &event)
{
	// TODO process only config buttons
	Command *cmd;

	switch (event.key.code)
	{
		case sf::Keyboard::A:
			cmd = CommandFactory::instance().create(COMMAND::MOVE_LEFT);
			break;
		case sf::Keyboard::W:
			cmd = CommandFactory::instance().create(COMMAND::MOVE_UP);
			break;
		case sf::Keyboard::S:
			cmd = CommandFactory::instance().create(COMMAND::MOVE_DOWN);
			break;
		case sf::Keyboard::D:
			cmd = CommandFactory::instance().create(COMMAND::MOVE_RIGHT);
			break;
		case sf::Keyboard::Escape:
			cmd = CommandFactory::instance().create(COMMAND::OPEN_HOLD_MENU);
			break;
		case sf::Keyboard::Return:
			cmd = CommandFactory::instance().create(COMMAND::RETURN_TO_MENU);
			break;
		default:
			cmd = CommandFactory::instance().create(COMMAND::EMPTY_OPERATION);
			break;
	}

	return cmd;
}

void GameFieldDrawer::draw()
{
	window_.render_object().clear();





	window_.render_object().display();
}
