#include <iostream>
#include <SFML/Graphics.hpp>

#include "Input/Implementation/SFML/SFMLInput.hpp"
#include "Engine/GameEngine.hpp"
#include "Render/SFML/SFMLRender.hpp"
#include "Render/Tracker.hpp"
#include "Command/Defines.hpp"
#include "Path.hpp"


int main()
{
	try
	{
		GameEngine engine;

		sf::RenderWindow window(sf::VideoMode(1366, 768), "Dungeon");
		SFMLInput input(game_dir + "/settings.cfg", window);
		SFMLRender render(window);
		Tracker tracker(&render);

		input.add_subscriber(&engine);
		engine.add_observer(&tracker);

		while (engine.is_running())
		{
			input.update();
			engine.update();
		}
	}
	catch(const std::invalid_argument& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch(...)
	{
		std::cerr << "Unknown exception" << '\n';
	}

	return 0;
}
