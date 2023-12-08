#include "FilePrinter.hpp"
#include <string>
#include <ios>


FilePrinter::FilePrinter(const std::string &filename) : file_(filename, std::ios::out) {}

std::ostream & FilePrinter::dump()
{
	return file_;
}
