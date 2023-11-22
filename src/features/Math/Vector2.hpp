#pragma once

#include <algorithm>
#include <cmath>

template<typename T>
class Vector2 {
 private:
  T x_, y_;
 public:
  // getters/setters
  T y() const;
  T x() const;

  void set_y(const T &y);
  void set_x(T x);

  // constructors
  Vector2(const T &ix, const T &iy);
  Vector2(const Vector2 &other);
  Vector2();

  [[nodiscard]] double distance(const Vector2 &other) const;

  // operators
  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator-(const Vector2 &other) const;
  Vector2 operator*(const Vector2 &other) const;
  Vector2 operator/(const Vector2 &other) const;
  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator*=(const Vector2 &other);
  Vector2 &operator/=(const Vector2 &other);
  Vector2 &operator=(const Vector2 &other);
  Vector2 &operator=(Vector2 &&other) noexcept;
  bool operator==(const Vector2 &other) const;
  bool operator<(const Vector2 &other) const;
};
template<typename T>
double Vector2<T>::distance(const Vector2 &other) const
{
	return std::sqrt(std::pow(x() - other.x(), 2) + std::pow(y() - other.y(), 2));
}

template<typename T>
Vector2<T>::Vector2(const T &ix, const T &iy): x_(ix), y_(iy)
{
}
template<typename T>
Vector2<T>::Vector2(): Vector2(0, 0)
{
}
template<typename T>
Vector2<T>::Vector2(const Vector2 &other) : Vector2()
{
	x_ = other.x_;
	y_ = other.y_;
}
template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &other) const
{
	Vector2<T> temp(*this);
	temp += other;
	return temp;
}
template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &other) const
{
	Vector2<T> temp(*this);
	temp -= other;
	return temp;
}
template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T> &other) const
{
	Vector2<T> temp(*this);
	temp *= other;
	return temp;
}
template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T> &other) const
{
	Vector2<T> temp(*this);
	temp /= other;
	return temp;
}
template<typename T>
Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &other)
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}
template<typename T>
Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &other)
{
	x_ -= other.x_;
	y_ -= other.y_;
	return *this;
}
template<typename T>
Vector2<T> &Vector2<T>::operator*=(const Vector2<T> &other)
{
	x_ *= other.x_;
	y_ *= other.y_;
	return *this;
}
template<typename T>
Vector2<T> &Vector2<T>::operator/=(const Vector2<T> &other)
{
	if (other.x_ != 0 && other.y_ != 0)
	{
		x_ /= other.x_;
		y_ /= other.y_;
	}
	return *this;
}
template<typename T>
T Vector2<T>::y() const
{
	return y_;
}
template<typename T>
void Vector2<T>::set_y(const T &y)
{
	y_ = y;
}
template<typename T>
T Vector2<T>::x() const
{
	return x_;
}
template<typename T>
void Vector2<T>::set_x(T x)
{
	x_ = x;
}
template<typename T>
Vector2<T> &Vector2<T>::operator=(const Vector2 &other)
{
	if (this != &other)
	{
		x_ = other.x_;
		y_ = other.y_;
	}
	return *this;
}
template<typename T>
Vector2<T> &Vector2<T>::operator=(Vector2 &&other) noexcept
{
	if (this != &other)
	{
		x_ = std::move(other.x_);
		y_ = std::move(other.y_);
	}
	return *this;
}
template<typename T>
bool Vector2<T>::operator==(const Vector2 &other) const
{
	return x_ == other.x_ && y_ == other.y_;
}
template<typename T>
bool Vector2<T>::operator<(const Vector2 &other) const
{
	if (x_ == other.x_)
	{
		return y_ < other.y_;
	}
	return x_ < other.x_;
}