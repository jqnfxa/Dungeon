#include "Engine/GameEngine.hpp"
#include "SetupLoggerConsole.hpp"
#include <iostream>


void SetupLoggerConsole::execute(GameEngine &engine)
{
	engine.setup_logger_console();
}
