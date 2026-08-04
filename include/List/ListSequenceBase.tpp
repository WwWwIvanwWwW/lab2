template <class T> void ListSequenceBase<T>::validateIndex(int index) const
{
	if (index < 0 || index >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T>
ListSequenceBase<T>::ListSequenceBase()
	: m_data(std::make_unique<LinkedList<T>>())
{
}

template <class T>
ListSequenceBase<T>::ListSequenceBase(T *items, int count)
	: m_data(std::make_unique<LinkedList<T>>(items, count))
{
}

template <class T>
ListSequenceBase<T>::ListSequenceBase(const LinkedList<T> &list)
	: m_data(std::make_unique<LinkedList<T>>(list))
{
}

template <class T>
ListSequenceBase<T>::ListSequenceBase(const DynamicArray<T> &array)
	: m_data(std::make_unique<LinkedList<T>>())
{
	for (int i = 0; i < array.GetSize(); ++i) {
		m_data->Append(array.Get(i));
	}
}

template <class T>
ListSequenceBase<T>::ListSequenceBase(const ListSequenceBase<T> &other)
	: m_data(std::make_unique<LinkedList<T>>(*other.m_data))
{
}

template <class T>
ListSequenceBase<T> &
ListSequenceBase<T>::operator=(const ListSequenceBase<T> &other)
{
	if (this != &other) {
		m_data = std::make_unique<LinkedList<T>>(*other.m_data);
	}
	return *this;
}

template <class T> T &ListSequenceBase<T>::operator[](int index)
{
	validateIndex(index);
	return (*m_data)[index];
}

template <class T> T ListSequenceBase<T>::GetFirst() const
{
	return m_data->GetFirst();
}

template <class T> T ListSequenceBase<T>::GetLast() const
{
	return m_data->GetLast();
}

template <class T> T ListSequenceBase<T>::Get(int index) const
{
	validateIndex(index);
	return m_data->Get(index);
}

template <class T> int ListSequenceBase<T>::GetLength() const
{
	return m_data->GetLength();
}
