#pragma once

#include "Logger/Messages/IMessage.hpp"
#include "Logger/Printers/IPrinter.hpp"
#include <vector>
#include <ostream>


class MessageBus
{
	std::vector<IPrinter *> receivers_;

	std::ostream &add_timestamp(std::ostream &out) const;
public:
	MessageBus() = default;
	~MessageBus();
	MessageBus(const MessageBus& other) = delete;
	const MessageBus& operator=(const MessageBus& other) = delete;

	void set_printer(IPrinter *new_printer);
	void reset_printers();
	void send_message(const IMessage *message);
};
