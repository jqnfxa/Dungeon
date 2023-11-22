#include "Cell.hpp"
#include "Event/PositiveEvents/Potion.hpp"
#include "Event/PositiveEvents/ShieldKit.hpp"
#include "Event/PositiveEvents/Star.hpp"
#include "Event/NegativeEvents/Spikes.hpp"
#include "Event/MovementEvents/RandomMine.hpp"
#include "Event/MovementEvents/Door.hpp"

Cell::Cell() : Cell(TYPE::MOVABLE)
{
}
Cell::Cell(TYPE type) : type_(type), event_(nullptr)
{
}
bool Cell::is_entrance() const
{
	return type_ == TYPE::ENTRANCE;
}
bool Cell::is_exit() const
{
	return type_ == TYPE::EXIT;
}
bool Cell::is_movable() const
{
	return type_ == TYPE::MOVABLE || is_exit() || is_entrance();
}
Cell::Cell(const Cell &other) noexcept : Cell()
{
	swap_values(other);
}
Cell &Cell::operator=(Cell &&other) noexcept
{
	if (this != &other)
	{
		swap_values(std::move(other));
	}
	return *this;
}
Cell::Cell(Cell &&other) noexcept: Cell()
{
	if (this != &other)
	{
		swap_values(std::move(other));
	}
}
Cell &Cell::operator=(const Cell &other) noexcept
{
	if (this != &other)
	{
		swap_values(other);
	}
	return *this;
}
void Cell::set_type(TYPE new_type)
{
	type_ = new_type;
}
Cell::~Cell()
{
	remove_event();
}
bool Cell::operator==(const Cell &other) const
{
	return type_ == other.type_/* && event_ == other.event_*/;
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
Cell::TYPE Cell::type() const
{
	return type_;
}
void Cell::swap_values(Cell &&other)
{
	std::swap(type_, other.type_);
	remove_event();
	add_event(other.event_);
	other.event_ = nullptr;
}
void Cell::swap_values(const Cell &other)
{
	type_ = other.type_;
	remove_event();
	add_event(other.event_ == nullptr ? nullptr : other.event_->copy());
}
std::ostream &operator<<(std::ostream &out, const Cell &cell)
{
	if (cell.is_entrance())
	{
		out << "[0]";
	}
	else if (cell.is_exit())
	{
		out << "[⛿]";
	}
	else if (cell.type_ == Cell::TYPE::WALL)
	{
		out << "[■]";
	}
	else if (cell.type_ == Cell::TYPE::PATH_PART)
	{
		out << "[△]";
	}
	else if (cell.has_door())
	{
		out << "[⥈]";
	}
	else
	{
		auto *active_event = cell.get_active_event();
		if (active_event == nullptr)
		{
			out << "[ ]";
		}
		else if (const auto *p = dynamic_cast<const Spikes *>(active_event); p != nullptr)
		{
			out << "[#]";
		}
		else if (const auto *k = dynamic_cast<const Potion *>(active_event); k != nullptr)
		{
			out << "[+]";
		}
		else if (const auto *d = dynamic_cast<const RandomMine *>(active_event); d != nullptr)
		{
			out << "[?]";
		}
		else if (const auto *m = dynamic_cast<const ShieldKit *>(active_event); m != nullptr)
		{
			out << "[⛨]";
		}
		else if (const auto *n = dynamic_cast<const Star *>(active_event); n != nullptr)
		{
			out << "[⭐]";
		}
		else if (const auto *t = dynamic_cast<const Key *>(active_event); t != nullptr)
		{
			out << "[⚿]";
		}
	}
	return out;
}
bool Cell::has_door() const
{
	return dynamic_cast<Door *>(event_) != nullptr;
}