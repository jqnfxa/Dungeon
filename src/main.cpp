#include <iostream>
#include "Game/State/TerminateState.hpp"
#include "Input/SFML/SfmlInput.hpp"
#include "Draw/Tracker.hpp"
#include "Draw/SFML/SfmlRenderer.hpp"

int main()
{
	try
	{
		GameEngine engine;
		SfmlInput input("/home/shard/.dungeon/settings.cfg");
		SfmlRenderer renderer(input);

		Tracker tracker(&renderer);
		engine.add_observer(&tracker);

		while (typeid(*engine.state()) != typeid(TerminateState))
		{
			input.update(engine.state());
			engine.update(input.last_command());
		}
	}
	catch (const std::invalid_argument &ia)
	{
		std::cerr << ia.what() << std::endl;
	}
	catch (const std::logic_error &le)
	{
		std::cerr << le.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}