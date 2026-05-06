#include <utility>
template <class T> void DynamicArray<T>::validateIndex(int index) const
{
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T> DynamicArray<T>::DynamicArray() : m_size(0) {}

template <class T>
DynamicArray<T>::DynamicArray(T *items, int count) : m_size(count)
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

template <class T> DynamicArray<T>::DynamicArray(int size) : m_size(size)
{
	if (size < 0) {
		throw std::invalid_argument("size cannot be negative");
	}
	m_data = std::make_unique<T[]>(size);
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
	: m_size(other.m_size)
{
	m_data = std::make_unique<T[]>(m_size);
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = other.m_data[i];
	}
}

template <class T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other)
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

template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&other) noexcept
	: m_data(std::move(other.m_data)), m_size(std::exchange(other.m_size, 0))
{
}

template <class T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray<T> &&other) noexcept
{
	if (this != &other) {
		m_data = std::move(other.m_data);
		m_size = std::exchange(other.m_size, 0);
	}
	return *this;
}

template <class T> T &DynamicArray<T>::operator[](int index)
{
	validateIndex(index);
	return m_data[index];
}

template <class T> const T &DynamicArray<T>::operator[](int index) const
{
	validateIndex(index);
	return m_data[index];
}

template <class T> T DynamicArray<T>::Get(int index) const
{
	validateIndex(index);
	return m_data[index];
}

template <class T> int DynamicArray<T>::GetSize() const { return m_size; }

template <class T> void DynamicArray<T>::Set(int index, T value)
{
	validateIndex(index);
	m_data[index] = value;
}

template <class T> void DynamicArray<T>::Resize(int newSize)
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