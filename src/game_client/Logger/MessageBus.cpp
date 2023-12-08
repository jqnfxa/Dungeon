#include "MessageBus.hpp"
#include <iomanip>
#include <chrono>


std::ostream &MessageBus::add_timestamp(std::ostream &out) const
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	// Convert to local time
	std::tm* local_time = std::localtime(&now);

	// Print the time in the format hours:minutes:seconds
	return out << '[' << std::setfill('0') << std::setw(2) << local_time->tm_hour << ":"
	<< std::setfill('0') << std::setw(2) << local_time->tm_min << ":"
	<< std::setfill('0') << std::setw(2) << local_time->tm_sec << ']';
}

MessageBus::~MessageBus()
{
	reset_printers();
}

void MessageBus::set_printer(IPrinter *new_printer)
{
	if (new_printer != nullptr)
	{
		receivers_.push_back(new_printer);
	}
}

void MessageBus::reset_printers()
{
	for (auto &receiver : receivers_)
	{
		delete receiver;
	}

	receivers_.clear();
}

void MessageBus::send_message(const IMessage *message)
{
	if (message == nullptr)
	{
		return;
	}

	for (auto &receiver : receivers_)
	{
		add_timestamp(receiver->dump()) << ": " << message;
	}

	delete message;
}
