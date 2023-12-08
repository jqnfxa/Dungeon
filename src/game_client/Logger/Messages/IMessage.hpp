#pragma once

#include <string>
#include <iostream>


class IMessage
{
public:
	virtual ~IMessage() = default;
	virtual std::string to_string() const = 0;
	friend std::ostream &operator<<(std::ostream &out, const IMessage *message)
	{
		if (message != nullptr)
		{
			out << message->to_string() << '\n';
		}

		return out;
	}
};
