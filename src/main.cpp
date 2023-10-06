#include <SFML/Graphics.hpp>
#include "GUI/Window.hpp"
#include "Game/GameEngine.hpp"
#include "Input/SFML/SFMLInput.hpp"

int main()
{
	GameEngine game;
	Window window(game, sf::VideoMode(1366, 768), "Dungeon");
	SFMLInput input(window);

	while (game.state() != GameState::TERMINATE)
	{
		input.update();
		game.update(input.command());
		window.draw();
	}
	return 0;
}
