#pragma once

#include <memory>
#include <stdexcept>

template <class T> class DynamicArray
{
  private:
	std::unique_ptr<T[]> m_data;
	int m_size = 0;

	void validateIndex(int index) const
	{
		if (index < 0 || index >= m_size) {
			throw std::out_of_range("IndexOutOfRange");
		}
	}

  public:
	DynamicArray() : m_size(0) {}

	DynamicArray(T *items, int count) : m_size(count)
	{
		if (count < 0) {
			throw std::invalid_argument("count cannot be negative");
		}
		if (items == nullptr && count > 0) {
			throw std::invalid_argument("items is null but count > 0");
		}

		m_data = std::make_unique<T[]>(count);
		for (int i = 0; i < count; ++i) {
			m_data[i] = items[i];
		}
	}

	explicit DynamicArray(int size) : m_size(size)
	{
		if (size < 0) {
			throw std::invalid_argument("size cannot be negative");
		}
		m_data = std::make_unique<T[]>(size);
	}

	DynamicArray(const DynamicArray<T> &other) : m_size(other.m_size)
	{
		m_data = std::make_unique<T[]>(m_size);
		for (int i = 0; i < m_size; ++i) {
			m_data[i] = other.m_data[i];
		}
	}

	DynamicArray<T> &operator=(const DynamicArray<T> &other)
	{
		if (this != &other) {
			auto newData = std::make_unique<T[]>(other.m_size);
			for (int i = 0; i < other.m_size; ++i) {
				newData[i] = other.m_data[i];
			}
			m_data = std::move(newData);
			m_size = other.m_size;
		}
		return *this;
	}

	DynamicArray(DynamicArray<T> &&other) noexcept
		: m_data(std::move(other.m_data)), m_size(other.m_size)
	{
		other.m_size = 0;
	}

	DynamicArray<T> &operator=(DynamicArray<T> &&other) noexcept
	{
		if (this != &other) {
			m_data = std::move(other.m_data);
			m_size = other.m_size;
			other.m_size = 0;
		}
		return *this;
	}

	~DynamicArray() = default;

	T &operator[](int index)
	{
		validateIndex(index);
		return m_data[index];
	}

	const T &operator[](int index) const
	{
		validateIndex(index);
		return m_data[index];
	}

	T Get(int index) const
	{
		validateIndex(index);
		return m_data[index];
	}

	int GetSize() const { return m_size; }

	void Set(int index, T value)
	{
		validateIndex(index);
		m_data[index] = value;
	}

	void Resize(int newSize)
	{
		if (newSize < 0) {
			throw std::invalid_argument("newSize cannot be negative");
		}

		if (newSize == m_size) {
			return;
		}

		auto newData = std::make_unique<T[]>(newSize);
		int copyCount = (newSize < m_size) ? newSize : m_size;

		for (int i = 0; i < copyCount; ++i) {
			newData[i] = std::move(m_data[i]);
		}

		m_data = std::move(newData);
		m_size = newSize;
	}
};