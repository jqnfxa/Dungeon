#include <iostream>
#include <SFML/Graphics.hpp>

#include "Input/Implementation/SFML/SFMLInput.hpp"
#include "Engine/GameEngine.hpp"
#include "Render/SFML/SFMLRender.hpp"
#include "Render/Tracker.hpp"
#include "Command/Defines.hpp"
#include "Path.hpp"
#include "Logger/MessageBus.hpp"


int main()
{
	try
	{
		MessageBus logger;
		GameEngine engine(logger);

		sf::RenderWindow window(sf::VideoMode(1366, 768), "Dungeon");
		SFMLInput input(game_dir + "/settings.cfg", window, logger);
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
	catch (const std::ios_base::failure& e)
	{
		std::cout << "Caught an ios_base::failure.\n"
			<< "Explanatory string: " << e.what() << '\n'
			<< "Error code: " << e.code() << '\n';
	}
	catch(...)
	{
		std::cerr << "Unknown exception" << '\n';
	}

	return 0;
}
