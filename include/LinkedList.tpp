template <class T>
LinkedList<T>::Node::Node(const T &value) : data(value), next(nullptr)
{
}

template <class T> void LinkedList<T>::validateIndex(int index) const
{
	if (index < 0 || index >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T>
typename LinkedList<T>::Node *LinkedList<T>::getNode(int index) const
{
	validateIndex(index);
	Node *current = m_head.get();
	for (int i = 0; i < index; ++i) {
		current = current->next.get();
	}
	return current;
}

template <class T>
LinkedList<T>::LinkedList() : m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

template <class T>
LinkedList<T>::LinkedList(T *items, int count)
	: m_head(nullptr), m_tail(nullptr), m_length(0)
{
	if (count < 0) {
		throw std::invalid_argument("count cannot be negative");
	}
	if (items == nullptr && count > 0) {
		throw std::invalid_argument("items is null but count > 0");
	}

	for (int i = 0; i < count; ++i) {
		Append(items[i]);
	}
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
	: m_head(nullptr), m_tail(nullptr), m_length(0)
{
	Node *current = other.m_head.get();
	while (current != nullptr) {
		Append(current->data);
		current = current->next.get();
	}
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
	if (this != &other) {
		LinkedList<T> temp(other);
		swap(temp);
	}
	return *this;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) noexcept
	: m_head(std::move(other.m_head)),
	  m_tail(std::exchange(other.m_tail, nullptr)),
	  m_length(std::exchange(other.m_length, 0))
{
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&other) noexcept
{
	if (this != &other) {
		m_head = std::move(other.m_head);
		m_tail = std::exchange(other.m_tail, nullptr);
		m_length = std::exchange(other.m_length, 0);
	}
	return *this;
}

template <class T> T &LinkedList<T>::operator[](int index)
{
	validateIndex(index);
	return getNode(index)->data;
}

template <class T> void LinkedList<T>::swap(LinkedList<T> &other) noexcept
{
	std::swap(m_head, other.m_head);
	std::swap(m_tail, other.m_tail);
	std::swap(m_length, other.m_length);
}

template <class T> T LinkedList<T>::GetFirst() const
{
	if (m_length == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_head->data;
}

template <class T> T LinkedList<T>::GetLast() const
{
	if (m_length == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_tail->data;
}

template <class T> T LinkedList<T>::Get(int index) const
{
	return getNode(index)->data;
}

template <class T>
LinkedList<T> LinkedList<T>::GetSubList(int startIndex, int endIndex) const
{
	if (startIndex < 0 || startIndex >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (endIndex < 0 || endIndex >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (startIndex > endIndex) {
		throw std::invalid_argument(
			"startIndex cannot be greater than endIndex");
	}

	LinkedList<T> sublist;
	Node *current = getNode(startIndex);
	for (int i = startIndex; i <= endIndex; ++i) {
		sublist.Append(current->data);
		current = current->next.get();
	}
	return sublist;
}

template <class T> int LinkedList<T>::GetLength() const { return m_length; }

template <class T> void LinkedList<T>::Append(T item)
{
	auto newNode = std::make_unique<Node>(item);
	Node *newNodePtr = newNode.get();

	if (m_head == nullptr) {
		m_head = std::move(newNode);
		m_tail = newNodePtr;
	} else {
		m_tail->next = std::move(newNode);
		m_tail = newNodePtr;
	}
	++m_length;
}

template <class T> void LinkedList<T>::Prepend(T item)
{
	auto newNode = std::make_unique<Node>(item);
	newNode->next = std::move(m_head);
	m_head = std::move(newNode);

	if (m_tail == nullptr) {
		m_tail = m_head.get();
	}
	++m_length;
}

template <class T> void LinkedList<T>::InsertAt(T item, int index)
{
	if (index == 0) {
		Prepend(item);
		return;
	}

	if (index == m_length) {
		Append(item);
		return;
	}

	validateIndex(index);

	Node *prev = getNode(index - 1);
	auto newNode = std::make_unique<Node>(item);
	newNode->next = std::move(prev->next);
	prev->next = std::move(newNode);
	++m_length;
}

template <class T>
LinkedList<T> LinkedList<T>::Concat(const LinkedList<T> &list) const
{
	LinkedList<T> result;

	Node *current = m_head.get();
	while (current != nullptr) {
		result.Append(current->data);
		current = current->next.get();
	}

	current = list.m_head.get();
	while (current != nullptr) {
		result.Append(current->data);
		current = current->next.get();
	}

	return result;
}