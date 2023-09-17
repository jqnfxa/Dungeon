#include <algorithm>
#include "Cell.hpp"

Cell::Cell() : Cell(Type::movable)
{
}
Cell::Cell(Type type) : type_(type), event_(nullptr)
{
}
bool Cell::is_entrance() const
{
	return type_ == Type::start;
}
bool Cell::is_exit() const
{
	return type_ == Type::finish;
}
bool Cell::is_movable() const
{
	return type_ == Type::movable || is_exit() || is_entrance();
}
Cell::Cell(const Cell &other) : Cell()
{
	*this = other;
}
Cell &Cell::operator=(Cell &&other) noexcept
{
	if (this != &other)
	{
		type_ = std::move(other.type_);
		remove_event();
		event_ = std::move(other.event_);
		other.event_ = nullptr;
	}
	return *this;
}
Cell::Cell(Cell &&other) noexcept: Cell()
{
	*this = std::move(other);
}
Cell &Cell::operator=(const Cell &other) noexcept
{
	if (this != &other)
	{
		type_ = other.type_;
		remove_event();
		event_ = other.event_ == nullptr ? nullptr : other.event_->copy();
	}
	return *this;
}
void Cell::set_type(Type new_type)
{
	type_ = new_type;
}
Cell::~Cell()
{
	remove_event();
}
bool Cell::operator==(const Cell &other) const
{
	// TODO check for events
	return type_ == other.type_;
}
const EventInterface *Cell::get_active_event() const
{
	return event_;
}
void Cell::add_event(EventInterface *event)
{
	remove_event();
	event_ = event;
}
void Cell::remove_event()
{
	delete event_;
	event_ = nullptr;
}
