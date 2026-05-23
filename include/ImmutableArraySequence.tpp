template <class T>
void ImmutableArraySequence<T>::validateIndex(int index) const
{
	if (index < 0 || index >= GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence()
	: m_data(std::make_unique<DynamicArray<T>>())
{
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T *items, int count)
	: m_data(std::make_unique<DynamicArray<T>>(items, count))
{
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T> &array)
	: m_data(std::make_unique<DynamicArray<T>>(array))
{
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const LinkedList<T> &list)
	: m_data(std::make_unique<DynamicArray<T>>())
{
	for (int i = 0; i < list.GetLength(); ++i) {
		m_data->Resize(m_data->GetSize() + 1);
		m_data->Set(m_data->GetSize() - 1, list.Get(i));
	}
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(
	const ImmutableArraySequence<T> &other)
	: m_data(std::make_unique<DynamicArray<T>>(*other.m_data))
{
}

template <class T>
ImmutableArraySequence<T> &
ImmutableArraySequence<T>::operator=(const ImmutableArraySequence<T> &other)
{
	if (this != &other) {
		m_data = std::make_unique<DynamicArray<T>>(*other.m_data);
	}
	return *this;
}

template <class T>
const T &ImmutableArraySequence<T>::operator[](int index) const
{
	validateIndex(index);
	return (*m_data)[index];
}

template <class T> T ImmutableArraySequence<T>::GetFirst() const
{
	if (GetLength() == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_data->Get(0);
}

template <class T> T ImmutableArraySequence<T>::GetLast() const
{
	if (GetLength() == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_data->Get(GetLength() - 1);
}

template <class T> T ImmutableArraySequence<T>::Get(int index) const
{
	validateIndex(index);
	return m_data->Get(index);
}

template <class T>
std::unique_ptr<Sequence<T>>
ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const
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

	auto subseq = std::make_unique<ImmutableArraySequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(m_data->Get(i));
	}
	return subseq;
}

template <class T> int ImmutableArraySequence<T>::GetLength() const
{
	return m_data->GetSize();
}

template <class T> void ImmutableArraySequence<T>::Append(T item)
{
	int newSize = m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	for (int i = 0; i < m_data->GetSize(); ++i) {
		newData->Set(i, m_data->Get(i));
	}
	newData->Set(m_data->GetSize(), item);
	m_data = std::move(newData);
}

template <class T> void ImmutableArraySequence<T>::Prepend(T item)
{
	int newSize = m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	newData->Set(0, item);
	for (int i = 0; i < m_data->GetSize(); ++i) {
		newData->Set(i + 1, m_data->Get(i));
	}
	m_data = std::move(newData);
}

template <class T> void ImmutableArraySequence<T>::InsertAt(T item, int index)
{
	if (index == 0) {
		Prepend(item);
		return;
	}
	if (index == GetLength()) {
		Append(item);
		return;
	}

	validateIndex(index);

	int newSize = m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	for (int i = 0; i < index; ++i) {
		newData->Set(i, m_data->Get(i));
	}
	newData->Set(index, item);
	for (int i = index; i < m_data->GetSize(); ++i) {
		newData->Set(i + 1, m_data->Get(i));
	}
	m_data = std::move(newData);
}

template <class T>
std::unique_ptr<Sequence<T>>
ImmutableArraySequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<ImmutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		result->Append(m_data->Get(i));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		result->Append(other->Get(i));
	}
	return result;
}