#pragma once

#include "DynamicArray.hpp"
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

template <class T> class Vector
{
  private:
	std::unique_ptr<DynamicArray<T>> m_data;
	int m_size;

	void validateIndex(int index) const;
	void validateSize(const Vector<T> &other) const;

  public:
	Vector();
	explicit Vector(int size);
	Vector(const Sequence<T> &seq);
	Vector(const Vector<T> &other);
	Vector(Vector<T> &&other) noexcept;
	Vector<T> &operator=(const Vector<T> &other);
	Vector<T> &operator=(Vector<T> &&other) noexcept;
	~Vector() = default;

	int GetSize() const;
	T Get(int index) const;
	void Set(int index, T value);

	T &operator[](int index);
	const T &operator[](int index) const;

	Vector<T> operator+(const Vector<T> &other) const;
	Vector<T> &operator+=(const Vector<T> &other);
	Vector<T> operator-(const Vector<T> &other) const;
	Vector<T> &operator-=(const Vector<T> &other);
	Vector<T> operator*(const T &scalar) const;
	Vector<T> &operator*=(const T &scalar);
	bool operator==(const Vector<T> &other) const;
	bool operator!=(const Vector<T> &other) const;

	T Norm() const;
	T ScalarProduct(const Vector<T> &other) const;

	std::unique_ptr<Sequence<T>> ToSequence() const;
	std::string ToString() const;
};

#include "Vector.tpp"