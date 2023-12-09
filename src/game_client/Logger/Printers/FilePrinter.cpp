#include "FilePrinter.hpp"
#include <string>
#include <ios>


FilePrinter::FilePrinter(const std::string &filename) : file_(filename, std::ios::out)
{
	if (!file_.is_open())
	{
		throw std::ios_base::failure("Failed to open file");
	}
}

std::ostream & FilePrinter::dump()
{
	return file_;
}
