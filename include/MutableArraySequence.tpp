template <class T>
std::unique_ptr<Sequence<T>>
MutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const
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

	auto subseq = std::make_unique<MutableArraySequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(m_data->Get(i));
	}
	return subseq;
}

template <class T> void MutableArraySequence<T>::Append(T item)
{
	m_data->Resize(m_data->GetSize() + 1);
	m_data->Set(m_data->GetSize() - 1, item);
}

template <class T> void MutableArraySequence<T>::Prepend(T item)
{
	int newSize = m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	newData->Set(0, item);
	for (int i = 0; i < m_data->GetSize(); ++i) {
		newData->Set(i + 1, m_data->Get(i));
	}
	m_data = std::move(newData);
}

template <class T> void MutableArraySequence<T>::InsertAt(T item, int index)
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
MutableArraySequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		result->Append(m_data->Get(i));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		result->Append(other->Get(i));
	}
	return result;
}

template <class T>
std::unique_ptr<Sequence<T>>
MutableArraySequence<T>::Map(std::function<T(const T &)> func) const
{
	auto result = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		result->Append(func(m_data->Get(i)));
	}
	return result;
}

template <class T>
T MutableArraySequence<T>::Reduce(std::function<T(const T &, const T &)> func,
								  T c) const
{
	T result = c;
	for (int i = 0; i < GetLength(); ++i) {
		result = func(m_data->Get(i), result);
	}
	return result;
}