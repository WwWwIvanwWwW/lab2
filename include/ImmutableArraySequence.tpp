template <class T>
std::unique_ptr<Sequence<T>>
ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
	if (startIndex < 0 || startIndex >= this->GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (endIndex < 0 || endIndex >= this->GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (startIndex > endIndex) {
		throw std::invalid_argument(
			"startIndex cannot be greater than endIndex");
	}

	auto subseq = std::make_unique<ImmutableArraySequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(this->m_data->Get(i));
	}
	return subseq;
}

template <class T> void ImmutableArraySequence<T>::Append(T item)
{
	int newSize = this->m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	for (int i = 0; i < this->m_data->GetSize(); ++i) {
		newData->Set(i, this->m_data->Get(i));
	}
	newData->Set(this->m_data->GetSize(), item);
	this->m_data = std::move(newData);
}

template <class T> void ImmutableArraySequence<T>::Prepend(T item)
{
	int newSize = this->m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	newData->Set(0, item);
	for (int i = 0; i < this->m_data->GetSize(); ++i) {
		newData->Set(i + 1, this->m_data->Get(i));
	}
	this->m_data = std::move(newData);
}

template <class T> void ImmutableArraySequence<T>::InsertAt(T item, int index)
{
	if (index == 0) {
		Prepend(item);
		return;
	}
	if (index == this->GetLength()) {
		Append(item);
		return;
	}

	this->validateIndex(index);

	int newSize = this->m_data->GetSize() + 1;
	auto newData = std::make_unique<DynamicArray<T>>(newSize);
	for (int i = 0; i < index; ++i) {
		newData->Set(i, this->m_data->Get(i));
	}
	newData->Set(index, item);
	for (int i = index; i < this->m_data->GetSize(); ++i) {
		newData->Set(i + 1, this->m_data->Get(i));
	}
	this->m_data = std::move(newData);
}

template <class T>
std::unique_ptr<Sequence<T>>
ImmutableArraySequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<ImmutableArraySequence<T>>();
	for (int i = 0; i < this->GetLength(); ++i) {
		result->Append(this->m_data->Get(i));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		result->Append(other->Get(i));
	}
	return result;
}

template <class T>
std::unique_ptr<Sequence<T>>
ImmutableArraySequence<T>::Map(std::function<T(const T &)> func) const
{
	auto result = std::make_unique<ImmutableArraySequence<T>>();
	for (int i = 0; i < this->GetLength(); ++i) {
		result->Append(func(this->m_data->Get(i)));
	}
	return result;
}

template <class T>
T ImmutableArraySequence<T>::Reduce(std::function<T(const T &, const T &)> func,
									T c) const
{
	T result = c;
	for (int i = 0; i < this->GetLength(); ++i) {
		result = func(this->m_data->Get(i), result);
	}
	return result;
}