#pragma once

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

  // TODO
  // Event *get_active_event();
  // void add_event(Event *event);
  // void remove_event();
 private:
  Type type_;
};