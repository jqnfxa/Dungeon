#include <iostream>
#include <SFML/Graphics.hpp>

#include "Input/Implementation/SFML/SFMLInput.hpp"
#include "Engine/GameEngine.hpp"
#include "Render/SFML/SFMLRender.hpp"
#include "Render/Tracker.hpp"
#include "Command/Defines.hpp"


// TODO: add try/catch
int main()
{
	GameEngine engine;

	sf::RenderWindow window(sf::VideoMode(1366, 768), "Dungeon");
	SFMLInput input("/home/shard/.dungeon/settings.cfg", window);
	SFMLRender render(window);
	Tracker tracker(&render);

	input.add_subscriber(&engine);
	engine.add_observer(&tracker);

	while (engine.is_running())
	{
		input.update();
		engine.update();
	}

	return 0;
}
