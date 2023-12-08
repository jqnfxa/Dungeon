#include "ConsolePrinter.hpp"
#include <iostream>


ConsolePrinter::ConsolePrinter() : stream_(std::cout) {}

std::ostream &ConsolePrinter::dump()
{
	return std::cout;
}
