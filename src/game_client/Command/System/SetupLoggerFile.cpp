#include "Engine/GameEngine.hpp"
#include "SetupLoggerFile.hpp"


void SetupLoggerFile::execute(GameEngine &engine)
{
	engine.setup_logger_file();
}
