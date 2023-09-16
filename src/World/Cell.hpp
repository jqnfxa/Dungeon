#pragma once

#include "Event/Interface/EventInterface.hpp"

class Cell {
 public:
  enum Type {
	  start, finish, movable, wall
  };
 public:
  Cell();
  ~Cell();
  explicit Cell(const Type &type);
  Cell(const Cell &other);
  Cell(Cell &&other) noexcept;
  Cell &operator=(const Cell &other) noexcept;
  Cell &operator=(Cell &&other) noexcept;
  bool operator==(const Cell &other) const;

  void set_type(const Type &new_type);

  [[nodiscard]] bool is_entrance() const;
  [[nodiscard]] bool is_exit() const;
  [[nodiscard]] bool is_movable() const;

  [[nodiscard]] const EventInterface *get_active_event() const;
  void add_event(EventInterface *event);
  void remove_event();
 private:
  Type type_;
  EventInterface *event_;
};