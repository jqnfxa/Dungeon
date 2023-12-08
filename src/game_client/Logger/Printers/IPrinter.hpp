#pragma once

#include <ostream>


class IPrinter
{
public:
	virtual ~IPrinter() = default;
	virtual std::ostream &dump() = 0;
};
