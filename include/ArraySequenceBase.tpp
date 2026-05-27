#include "ArraySequenceBase.hpp"
template <class T> void ArraySequenceBase<T>::validateIndex(int index) const
{
	if (index < 0 || index >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T>
ArraySequenceBase<T>::ArraySequenceBase()
	: m_data(std::make_unique<DynamicArray<T>>())
{
}

template <class T>
ArraySequenceBase<T>::ArraySequenceBase(T *items, int count)
	: m_data(std::make_unique<DynamicArray<T>>(items, count))
{
}

template <class T>
ArraySequenceBase<T>::ArraySequenceBase(const DynamicArray<T> &array)
	: m_data(std::make_unique<DynamicArray<T>>(array))
{
}

template <class T>
ArraySequenceBase<T>::ArraySequenceBase(const LinkedList<T> &list)
	: m_data(std::make_unique<DynamicArray<T>>())
{
	for (int i = 0; i < list.GetLength(); ++i) {
		m_data->Resize(m_data->GetSize() + 1);
		m_data->Set(m_data->GetSize() - 1, list.Get(i));
	}
}

template <class T>
ArraySequenceBase<T>::ArraySequenceBase(const ArraySequenceBase<T> &other)
	: m_data(std::make_unique<DynamicArray<T>>(*other.m_data))
{
}

template <class T>
ArraySequenceBase<T> &
ArraySequenceBase<T>::operator=(const ArraySequenceBase<T> &other)
{
	if (this != &other) {
		m_data = std::make_unique<DynamicArray<T>>(*other.m_data);
	}
	return *this;
}

template <class T> const T &ArraySequenceBase<T>::operator[](int index) const
{
	validateIndex(index);
	return (*m_data)[index];
}

template <class T> T ArraySequenceBase<T>::GetFirst() const
{
	if (GetLength() == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_data->Get(0);
}

template <class T> T ArraySequenceBase<T>::GetLast() const
{
	if (GetLength() == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_data->Get(GetLength() - 1);
}

template <class T> T ArraySequenceBase<T>::Get(int index) const
{
	validateIndex(index);
	return m_data->Get(index);
}

template <class T> int ArraySequenceBase<T>::GetLength() const
{
	return m_data->GetSize();
}
