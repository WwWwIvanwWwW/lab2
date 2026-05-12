#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <memory>
#include <stdexcept>

template <class T> class DynamicArray
{
  private:
	std::unique_ptr<T[]> m_data;
	int m_size = 0;

	void validateIndex(int index) const;

  public:
	DynamicArray();
	DynamicArray(T *items, int count);
	explicit DynamicArray(int size);
	DynamicArray(const DynamicArray<T> &other);
	DynamicArray<T> &operator=(const DynamicArray<T> &other);
	DynamicArray(DynamicArray<T> &&other) noexcept;
	DynamicArray<T> &operator=(DynamicArray<T> &&other) noexcept;
	~DynamicArray() = default;

	T &operator[](int index);
	const T &operator[](int index) const;

	T Get(int index) const;
	int GetSize() const;
	void Set(int index, T value);
	void Resize(int newSize);
};

#include "DynamicArray.tpp"