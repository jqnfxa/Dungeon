#include <cstdlib>
#include <string>

std::string home(std::getenv("HOME"));
std::string game_dir(home + "/.dungeon");
