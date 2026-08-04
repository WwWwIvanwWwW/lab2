template <class T> void Vector<T>::validateIndex(int index) const
{
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template <class T> void Vector<T>::validateSize(const Vector<T> &other) const
{
	if (m_size != other.m_size) {
		throw std::invalid_argument("Vector sizes do not match");
	}
}

template <class T>
Vector<T>::Vector() : m_data(std::make_unique<DynamicArray<T>>()), m_size(0)
{
}

template <class T>
Vector<T>::Vector(int size)
	: m_data(std::make_unique<DynamicArray<T>>(size)), m_size(size)
{
	if (size < 0) {
		throw std::invalid_argument("Size cannot be negative");
	}
}

template <class T>
Vector<T>::Vector(const Sequence<T> &seq)
	: m_data(std::make_unique<DynamicArray<T>>()), m_size(seq.GetLength())
{
	for (int i = 0; i < m_size; ++i) {
		m_data->Set(i, seq.Get(i));
	}
}

template <class T>
Vector<T>::Vector(const Vector<T> &other)
	: m_data(std::make_unique<DynamicArray<T>>()), m_size(other.m_size)
{
	for (int i = 0; i < m_size; ++i) {
		m_data->Set(i, other.m_data->Get(i));
	}
}

template <class T>
Vector<T>::Vector(Vector<T> &&other) noexcept
	: m_data(std::move(other.m_data)), m_size(std::exchange(other.m_size, 0))
{
}

template <class T> Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
	if (this != &other) {
		auto newData = std::make_unique<DynamicArray<T>>(other.m_size);
		for (int i = 0; i < other.m_size; ++i) {
			newData->Set(i, other.m_data->Get(i));
		}
		m_data = std::move(newData);
		m_size = other.m_size;
	}
	return *this;
}

template <class T> Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
	if (this != &other) {
		m_data = std::move(other.m_data);
		m_size = std::exchange(other.m_size, 0);
	}
	return *this;
}

template <class T> int Vector<T>::GetSize() const { return m_size; }

template <class T> T Vector<T>::Get(int index) const
{
	validateIndex(index);
	return m_data->Get(index);
}

template <class T> void Vector<T>::Set(int index, T value)
{
	validateIndex(index);
	m_data->Set(index, value);
}

template <class T> T &Vector<T>::operator[](int index)
{
	validateIndex(index);
	return (*m_data)[index];
}

template <class T> const T &Vector<T>::operator[](int index) const
{
	validateIndex(index);
	return (*m_data)[index];
}

template <class T> Vector<T> Vector<T>::operator+(const Vector<T> &other) const
{
	validateSize(other);
	Vector<T> result(m_size);
	for (int i = 0; i < m_size; ++i) {
		result.Set(i, m_data->Get(i) + other.m_data->Get(i));
	}
	return result;
}

template <class T> Vector<T> &Vector<T>::operator+=(const Vector<T> &other)
{
	validateSize(other);
	for (int i = 0; i < m_size; ++i) {
		T newValue = m_data->Get(i) + other.m_data->Get(i);
		m_data->Set(i, newValue);
	}
	return *this;
}

template <class T> Vector<T> Vector<T>::operator-(const Vector<T> &other) const
{
	validateSize(other);
	Vector<T> result(m_size);
	for (int i = 0; i < m_size; ++i) {
		result.Set(i, m_data->Get(i) - other.m_data->Get(i));
	}
	return result;
}

template <class T> Vector<T> &Vector<T>::operator-=(const Vector<T> &other)
{
	validateSize(other);
	for (int i = 0; i < m_size; ++i) {
		T newValue = m_data->Get(i) - other.m_data->Get(i);
		m_data->Set(i, newValue);
	}
	return *this;
}

template <class T> Vector<T> Vector<T>::operator*(const T &scalar) const
{
	Vector<T> result(m_size);
	for (int i = 0; i < m_size; ++i) {
		result.Set(i, m_data->Get(i) * scalar);
	}
	return result;
}

template <class T> Vector<T> &Vector<T>::operator*=(const T &scalar)
{
	for (int i = 0; i < m_size; ++i) {
		m_data->Set(i, m_data->Get(i) * scalar);
	}
	return *this;
}

template <class T> bool Vector<T>::operator==(const Vector<T> &other) const
{
	if (m_size != other.m_size) {
		return false;
	}
	for (int i = 0; i < m_size; ++i) {
		if (m_data->Get(i) != other.m_data->Get(i)) {
			return false;
		}
	}
	return true;
}

template <class T> bool Vector<T>::operator!=(const Vector<T> &other) const
{
	return !(*this == other);
}

template <class T> T Vector<T>::Norm() const
{
	T sum = 0;
	for (int i = 0; i < m_size; ++i) {
		T val = m_data->Get(i);
		sum += val * val;
	}
	return std::sqrt(sum);
}

template <class T> T Vector<T>::ScalarProduct(const Vector<T> &other) const
{
	validateSize(other);
	T result = 0;
	for (int i = 0; i < m_size; ++i) {
		result += m_data->Get(i) * other.m_data->Get(i);
	}
	return result;
}

template <class T> std::unique_ptr<Sequence<T>> Vector<T>::ToSequence() const
{
	auto seq = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < m_size; ++i) {
		seq->Append(m_data->Get(i));
	}
	return seq;
}

template <class T> std::string Vector<T>::ToString() const
{
	if (m_size == 0) {
		return "[]";
	}

	std::string result = "[";
	for (int i = 0; i < m_size; ++i) {
		result += std::to_string(m_data->Get(i));
		if (i + 1 < m_size) {
			result += ", ";
		}
	}
	result += "]";
	return result;
}