#pragma once

#include "IPrinter.hpp"
#include <fstream>


class FilePrinter : public IPrinter
{
	std::ofstream file_;
public:
	FilePrinter(const std::string &filename);
	std::ostream &dump() override;
};
