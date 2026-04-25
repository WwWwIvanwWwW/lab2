template <class T> class ImmutableListSequence : public Sequence<T>
{
  private:
	std::unique_ptr<LinkedList<T>> m_data;

	void validateIndex(int index) const
	{
		if (index < 0 || index >= GetLength()) {
			throw std::out_of_range("IndexOutOfRange");
		}
	}

  public:
	ImmutableListSequence() : m_data(std::make_unique<LinkedList<T>>()) {}

	ImmutableListSequence(T *items, int count)
		: m_data(std::make_unique<LinkedList<T>>(items, count))
	{
	}

	ImmutableListSequence(const LinkedList<T> &list)
		: m_data(std::make_unique<LinkedList<T>>(list))
	{
	}

	ImmutableListSequence(const DynamicArray<T> &array)
		: m_data(std::make_unique<LinkedList<T>>())
	{
		for (int i = 0; i < array.GetSize(); ++i) {
			m_data->Append(array.Get(i));
		}
	}

	ImmutableListSequence(const ImmutableListSequence<T> &other)
		: m_data(std::make_unique<LinkedList<T>>(*other.m_data))
	{
	}

	ImmutableListSequence<T> &operator=(const ImmutableListSequence<T> &other)
	{
		if (this != &other) {
			m_data = std::make_unique<LinkedList<T>>(*other.m_data);
		}
		return *this;
	}

	ImmutableListSequence(ImmutableListSequence<T> &&other) noexcept = default;
	ImmutableListSequence<T> &
	operator=(ImmutableListSequence<T> &&other) noexcept = default;
	~ImmutableListSequence() = default;

	T GetFirst() const override { return m_data->GetFirst(); }

	T GetLast() const override { return m_data->GetLast(); }

	T Get(int index) const override
	{
		validateIndex(index);
		return m_data->Get(index);
	}

	std::unique_ptr<Sequence<T>> GetSubsequence(int startIndex,
												int endIndex) const override
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

		auto subseq = std::make_unique<ImmutableListSequence<T>>();
		for (int i = startIndex; i <= endIndex; ++i) {
			subseq->Append(m_data->Get(i));
		}
		return subseq;
	}

	int GetLength() const override { return m_data->GetLength(); }

	void Append(T item) override
	{
		auto newData = std::make_unique<LinkedList<T>>(*m_data);
		newData->Append(item);
		m_data = std::move(newData);
	}

	void Prepend(T item) override
	{
		auto newData = std::make_unique<LinkedList<T>>(*m_data);
		newData->Prepend(item);
		m_data = std::move(newData);
	}

	void InsertAt(T item, int index) override
	{
		auto newData = std::make_unique<LinkedList<T>>(*m_data);
		newData->InsertAt(item, index);
		m_data = std::move(newData);
	}

	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override
	{
		if (other == nullptr) {
			throw std::invalid_argument("other cannot be null");
		}

		auto result = std::make_unique<ImmutableListSequence<T>>();
		for (int i = 0; i < GetLength(); ++i) {
			result->Append(m_data->Get(i));
		}
		for (int i = 0; i < other->GetLength(); ++i) {
			result->Append(other->Get(i));
		}
		return result;
	}
};