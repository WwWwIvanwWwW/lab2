template <class T>
std::unique_ptr<Sequence<T>>
ImmutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
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

	auto subseq = std::make_unique<ImmutableListSequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(this->m_data->Get(i));
	}
	return subseq;
}

template <class T> void ImmutableListSequence<T>::Append(T item)
{
	auto newData = std::make_unique<LinkedList<T>>(*this->m_data);
	newData->Append(item);
	this->m_data = std::move(newData);
}

template <class T> void ImmutableListSequence<T>::Prepend(T item)
{
	auto newData = std::make_unique<LinkedList<T>>(*this->m_data);
	newData->Prepend(item);
	this->m_data = std::move(newData);
}

template <class T> void ImmutableListSequence<T>::InsertAt(T item, int index)
{
	auto newData = std::make_unique<LinkedList<T>>(*this->m_data);
	newData->InsertAt(item, index);
	this->m_data = std::move(newData);
}

template <class T>
std::unique_ptr<Sequence<T>>
ImmutableListSequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<ImmutableListSequence<T>>();
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
ImmutableListSequence<T>::Map(std::function<T(const T &)> func) const
{
	auto result = std::make_unique<ImmutableListSequence<T>>();
	for (int i = 0; i < this->GetLength(); ++i) {
		result->Append(func(this->Get(i)));
	}
	return result;
}

template <class T>
T ImmutableListSequence<T>::Reduce(std::function<T(const T &, const T &)> func,
								   T c) const
{
	T result = c;
	for (int i = 0; i < this->GetLength(); ++i) {
		result = func(this->Get(i), result);
	}
	return result;
}