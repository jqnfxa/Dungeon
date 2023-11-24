#pragma once

#include "Event/Interface/EventInterface.hpp"
#include <ostream>

class Cell {
 public:
  enum TYPE {
	  ENTRANCE, EXIT, MOVABLE, WALL, PATH_PART
  };
 public:
  Cell();
  ~Cell();
  explicit Cell(TYPE type);
  Cell(const Cell &other) noexcept;
  Cell(Cell &&other) noexcept;
  Cell &operator=(const Cell &other) noexcept;
  Cell &operator=(Cell &&other) noexcept;
  bool operator==(const Cell &other) const;

  void set_type(TYPE new_type);

  [[nodiscard]] bool is_entrance() const;
  [[nodiscard]] bool is_exit() const;
  [[nodiscard]] bool is_movable() const;
  [[nodiscard]] TYPE type() const;

  [[nodiscard]] const EventInterface *get_active_event() const;
  void add_event(EventInterface *event);
  void remove_event();
 private:
  TYPE type_;
  EventInterface *event_;

  void swap_values(Cell &&other);
  void swap_values(const Cell &other);
};
