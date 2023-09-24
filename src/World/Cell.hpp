#pragma once

#include "Event/Interface/EventInterface.hpp"

class Cell {
 public:
  enum Type {
	  ENTRANCE, EXIT, MOVABLE, WALL
  };
 public:
  Cell();
  ~Cell();
  explicit Cell(Type type);
  Cell(const Cell &other);
  Cell(Cell &&other) noexcept;
  Cell &operator=(const Cell &other) noexcept;
  Cell &operator=(Cell &&other) noexcept;
  bool operator==(const Cell &other) const;

  void set_type(Type new_type);

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