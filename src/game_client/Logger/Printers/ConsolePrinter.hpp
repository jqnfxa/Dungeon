#pragma once

#include "IPrinter.hpp"


class ConsolePrinter : public IPrinter
{
	std::ostream &stream_;
public:
	ConsolePrinter();
	std::ostream &dump() override;
};
