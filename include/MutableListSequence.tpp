template <class T> void MutableListSequence<T>::validateIndex(int index) const
{
	if (index < 0 || index >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T>
MutableListSequence<T>::MutableListSequence()
	: m_data(std::make_unique<LinkedList<T>>())
{
}

template <class T>
MutableListSequence<T>::MutableListSequence(T *items, int count)
	: m_data(std::make_unique<LinkedList<T>>(items, count))
{
}

template <class T>
MutableListSequence<T>::MutableListSequence(const LinkedList<T> &list)
	: m_data(std::make_unique<LinkedList<T>>(list))
{
}

template <class T>
MutableListSequence<T>::MutableListSequence(const DynamicArray<T> &array)
	: m_data(std::make_unique<LinkedList<T>>())
{
	for (int i = 0; i < array.GetSize(); ++i) {
		m_data->Append(array.Get(i));
	}
}

template <class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T> &other)
	: m_data(std::make_unique<LinkedList<T>>(*other.m_data))
{
}

template <class T>
MutableListSequence<T> &
MutableListSequence<T>::operator=(const MutableListSequence<T> &other)
{
	if (this != &other) {
		m_data = std::make_unique<LinkedList<T>>(*other.m_data);
	}
	return *this;
}

template <class T> T MutableListSequence<T>::GetFirst() const
{
	return m_data->GetFirst();
}

template <class T> T MutableListSequence<T>::GetLast() const
{
	return m_data->GetLast();
}

template <class T> T MutableListSequence<T>::Get(int index) const
{
	validateIndex(index);
	return m_data->Get(index);
}

template <class T>
std::unique_ptr<Sequence<T>>
MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
	if (startIndex < 0 || startIndex >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (endIndex < 0 || endIndex >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (startIndex > endIndex) {
		throw std::invalid_argument(
			"startIndex cannot be greater than endIndex");
	}

	auto subseq = std::make_unique<MutableListSequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(m_data->Get(i));
	}
	return subseq;
}

template <class T> int MutableListSequence<T>::GetLength() const
{
	return m_data->GetLength();
}

template <class T> void MutableListSequence<T>::Append(T item)
{
	m_data->Append(item);
}

template <class T> void MutableListSequence<T>::Prepend(T item)
{
	m_data->Prepend(item);
}

template <class T> void MutableListSequence<T>::InsertAt(T item, int index)
{
	m_data->InsertAt(item, index);
}

template <class T>
std::unique_ptr<Sequence<T>>
MutableListSequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<MutableListSequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		result->Append(m_data->Get(i));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		result->Append(other->Get(i));
	}
	return result;
}