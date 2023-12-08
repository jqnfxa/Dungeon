#include "Engine/GameEngine.hpp"
#include "SetupLoggerEmpty.hpp"


void SetupLoggerEmpty::execute(GameEngine &engine)
{
	engine.setup_logger_empty();
}
