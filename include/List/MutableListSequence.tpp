template <class T>
std::unique_ptr<Sequence<T>>
MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
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

	auto subseq = std::make_unique<MutableListSequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(this->m_data->Get(i));
	}
	return subseq;
}

template <class T> void MutableListSequence<T>::Append(T item)
{
	this->m_data->Append(item);
}

template <class T> void MutableListSequence<T>::Prepend(T item)
{
	this->m_data->Prepend(item);
}

template <class T> void MutableListSequence<T>::InsertAt(T item, int index)
{
	this->m_data->InsertAt(item, index);
}

template <class T>
std::unique_ptr<Sequence<T>>
MutableListSequence<T>::Concat(Sequence<T> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<MutableListSequence<T>>();
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
MutableListSequence<T>::Map(std::function<T(const T &)> func) const
{
	auto result = std::make_unique<MutableListSequence<T>>();
	for (int i = 0; i < this->GetLength(); ++i) {
		result->Append(func(this->Get(i)));
	}
	return result;
}

template <class T>
T MutableListSequence<T>::Reduce(std::function<T(const T &, const T &)> func,
								 T c) const
{
	T result = c;
	for (int i = 0; i < this->GetLength(); ++i) {
		result = func(this->Get(i), result);
	}
	return result;
}