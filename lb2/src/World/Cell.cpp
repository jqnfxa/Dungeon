#include <algorithm>
#include "Cell.hpp"

Cell::Cell() : Cell(Type::MOVABLE)
{
}
Cell::Cell(Type type) : type_(type), event_(nullptr)
{
}
Cell::~Cell()
{
	// release event resources
}
bool Cell::is_entrance() const
{
	return type_ == Type::ENTRANCE;
}
bool Cell::is_exit() const
{
	return type_ == Type::EXIT;
}
bool Cell::is_movable() const
{
	return type_ == Type::MOVABLE || is_exit() || is_entrance();
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
	}
	return *this;
}
void Cell::set_type(Type new_type)
{
	type_ = new_type;
}
bool Cell::operator==(const Cell &other) const
{
	// TODO check for events
	return type_ == other.type_;
}
