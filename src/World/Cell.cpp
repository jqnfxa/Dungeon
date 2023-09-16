#include <algorithm>
#include "Cell.hpp"

Cell::Cell() : Cell(Type::movable)
{
}
Cell::Cell(const Type &type) : type_(type)
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
Cell::Cell(const Cell &other)
{
	*this = other;
}
Cell &Cell::operator=(Cell &&other) noexcept
{
	if (this != &other)
	{
		type_ = std::move(other.type_);
	}
	return *this;
}
Cell::Cell(Cell &&other) noexcept
{
	*this = std::move(other);
}
Cell &Cell::operator=(const Cell &other) noexcept
{
	if (this != &other)
	{
		type_ = other.type_;
	}
	return *this;
}
void Cell::set_type(const Type &new_type)
{
	type_ = new_type;
}
Cell::~Cell()
{
	// release event resources
}
bool Cell::operator==(const Cell &other) const
{
	// TODO check for events
	return type_ == other.type_;
}
