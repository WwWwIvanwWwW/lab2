#include "LazySequence.hpp"

template <class T>
LazySequence<T>::LazySequence()
	: m_base(nullptr), m_op(nullptr), m_generator(nullptr),
	  m_memo(std::make_unique<MutableArraySequence<T>>()), m_isInfinite(false)
{
}

template <class T>
LazySequence<T>::LazySequence(T *items, int count)
	: m_base(nullptr), m_op(nullptr), m_generator(nullptr),
	  m_memo(std::make_unique<MutableArraySequence<T>>()), m_isInfinite(false)
{
	for (int i = 0; i < count; ++i) {
		m_memo->Append(items[i]);
	}
}

template <class T>
LazySequence<T>::LazySequence(Sequence<T> *seq)
	: m_base(nullptr), m_op(nullptr), m_generator(nullptr),
	  m_memo(std::make_unique<MutableArraySequence<T>>()), m_isInfinite(false)
{
	for (int i = 0; i < seq->GetLength(); ++i) {
		m_memo->Append(seq->Get(i));
	}
}

template <class T>
LazySequence<T>::LazySequence(std::function<T(Sequence<T> *)> func,
							  Sequence<T> *initial)
	: m_base(nullptr), m_op(nullptr),
	  m_generator(std::make_unique<Generator<T>>(func, nullptr)),
	  m_memo(std::make_unique<MutableArraySequence<T>>()), m_isInfinite(true)
{
	if (initial) {
		for (int i = 0; i < initial->GetLength(); ++i) {
			m_memo->Append(initial->Get(i));
		}
	}
	m_generator->SetContext(this);
}

template <class T>
LazySequence<T>::LazySequence(const LazySequence<T> &other)
	: m_base(other.m_base),
	  m_op(other.m_op ? std::make_unique<Operation>(*other.m_op) : nullptr),
	  m_generator(other.m_generator
					  ? std::make_unique<Generator<T>>(*other.m_generator)
					  : nullptr),
	  m_memo(std::make_unique<MutableArraySequence<T>>(*other.m_memo)),
	  m_isInfinite(other.m_isInfinite)
{
	if (m_generator) {
		m_generator->SetContext(this);
	}
}

template <class T>
LazySequence<T> &LazySequence<T>::operator=(const LazySequence<T> &other)
{
	if (this == &other)
		return *this;
	m_base = other.m_base;
	m_op = other.m_op ? std::make_unique<Operation>(*other.m_op) : nullptr;
	m_generator = other.m_generator
					  ? std::make_unique<Generator<T>>(*other.m_generator)
					  : nullptr;
	if (m_generator) {
		m_generator->SetContext(this);
	}
	m_memo = std::make_unique<MutableArraySequence<T>>(*other.m_memo);
	m_isInfinite = other.m_isInfinite;
	return *this;
}

template <class T>
LazySequence<T> &LazySequence<T>::operator=(LazySequence<T> &&other) noexcept
{
	if (this == &other)
		return *this;
	m_base = std::move(other.m_base);
	m_op = std::move(other.m_op);
	m_generator = std::move(other.m_generator);
	m_memo = std::move(other.m_memo);
	m_isInfinite = other.m_isInfinite;
	return *this;
}

template <class T> void LazySequence<T>::Materialize(int index) const
{
	if (m_generator) {
		while (index >= m_memo->GetLength()) {
			m_memo->Append(m_generator->GetNext());
		}
	}
}

template <class T> T LazySequence<T>::Compute(int index) const
{
	if (index < 0)
		throw std::out_of_range("IndexOutOfRange");

	if (m_op) {
		if (!m_base)
			throw std::logic_error("Operation without base");
		switch (m_op->type) {
		case OpType::Prepend:
			if (index == 0)
				return m_op->item;
			return m_base->Get(index - 1);
		case OpType::InsertAt:
			if (index == m_op->index)
				return m_op->item;
			if (index > m_op->index)
				return m_base->Get(index - 1);
			return m_base->Get(index);
		}
	}

	if (m_generator) {
		Materialize(index);
		return m_memo->Get(index);
	}

	if (index >= m_memo->GetLength()) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return m_memo->Get(index);
}

template <class T> int LazySequence<T>::ComputeLength() const
{
	if (m_isInfinite)
		return -1;

	if (m_op) {
		if (!m_base)
			throw std::logic_error("Operation without base");
		int baseLen = m_base->GetLength();
		switch (m_op->type) {
		case OpType::Prepend:
		case OpType::InsertAt:
			return baseLen + 1;
		}
	}

	if (m_generator) {
		while (m_generator->HasNext()) {
			m_memo->Append(m_generator->GetNext());
		}
		return m_memo->GetLength();
	}

	return m_memo->GetLength();
}

template <class T> T LazySequence<T>::GetFirst() const
{
	if (m_memo->GetLength() == 0 && !m_base && !m_generator) {
		throw std::out_of_range("Sequence is empty");
	}
	return Compute(0);
}

template <class T> T LazySequence<T>::GetLast() const
{
	if (m_isInfinite) {
		throw std::logic_error("Cannot get last element of infinite sequence");
	}
	int len = ComputeLength();
	if (len <= 0)
		throw std::out_of_range("Sequence is empty");
	return Compute(len - 1);
}

template <class T> T LazySequence<T>::Get(int index) const
{
	return Compute(index);
}

template <class T>
std::unique_ptr<Sequence<T>> LazySequence<T>::GetSubsequence(int startIndex,
															 int endIndex) const
{
	if (startIndex < 0 || endIndex < startIndex) {
		throw std::invalid_argument("Invalid indices");
	}

	if (m_isInfinite) {
		if (endIndex == -1) {
			auto newGenFunc =
				[base = std::make_shared<const LazySequence<T>>(*this),
				 startIndex](Sequence<T> *) mutable -> T {
				static int idx = startIndex;
				return base->Get(idx++);
			};
			auto newSeq = std::make_unique<LazySequence<T>>();
			newSeq->m_generator =
				std::make_unique<Generator<T>>(newGenFunc, nullptr);
			newSeq->m_generator->SetContext(newSeq.get());
			newSeq->m_isInfinite = true;
			return newSeq;
		} else {
			auto result = std::make_unique<MutableArraySequence<T>>();
			for (int i = startIndex; i <= endIndex; ++i) {
				result->Append(Get(i));
			}
			return std::make_unique<LazySequence<T>>(result.get());
		}
	}

	int len = ComputeLength();
	if (endIndex >= len)
		throw std::out_of_range("IndexOutOfRange");
	auto result = std::make_unique<MutableArraySequence<T>>();
	for (int i = startIndex; i <= endIndex; ++i) {
		result->Append(Get(i));
	}
	return std::make_unique<LazySequence<T>>(result.get());
}

template <class T> int LazySequence<T>::GetLength() const
{
	return ComputeLength();
}

template <class T> Cardinal LazySequence<T>::GetCardinalLength() const
{
	if (m_isInfinite)
		return Cardinal::Infinity();
	return Cardinal(ComputeLength());
}

template <class T> size_t LazySequence<T>::GetMaterializedCount() const
{
	return m_memo->GetLength();
}

template <class T> void LazySequence<T>::Append(T item)
{
	if (m_isInfinite) {
		throw std::logic_error("Cannot append to infinite sequence");
	}
	auto full = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		full->Append(Get(i));
	}
	full->Append(item);
	LazySequence<T> newSeq(full.get());
	*this = std::move(newSeq);
}

template <class T> void LazySequence<T>::Prepend(T item)
{
	auto newSeq = std::make_unique<LazySequence<T>>();
	newSeq->m_base = std::make_shared<const LazySequence<T>>(*this);
	newSeq->m_op = std::make_unique<Operation>();
	newSeq->m_op->type = OpType::Prepend;
	newSeq->m_op->item = item;
	newSeq->m_isInfinite = m_isInfinite;
	if (m_generator) {
		newSeq->m_generator = std::make_unique<Generator<T>>(*m_generator);
		newSeq->m_generator->SetContext(newSeq.get());
	}
	newSeq->m_memo = std::make_unique<MutableArraySequence<T>>(*m_memo);
	*this = std::move(*newSeq);
}

template <class T> void LazySequence<T>::InsertAt(T item, int index)
{
	if (index < 0)
		throw std::out_of_range("IndexOutOfRange");
	auto newSeq = std::make_unique<LazySequence<T>>();
	newSeq->m_base = std::make_shared<const LazySequence<T>>(*this);
	newSeq->m_op = std::make_unique<Operation>();
	newSeq->m_op->type = OpType::InsertAt;
	newSeq->m_op->item = item;
	newSeq->m_op->index = index;
	newSeq->m_isInfinite = m_isInfinite;
	if (m_generator) {
		newSeq->m_generator = std::make_unique<Generator<T>>(*m_generator);
		newSeq->m_generator->SetContext(newSeq.get());
	}
	newSeq->m_memo = std::make_unique<MutableArraySequence<T>>(*m_memo);
	*this = std::move(*newSeq);
}

template <class T>
std::unique_ptr<Sequence<T>> LazySequence<T>::Concat(Sequence<T> *other) const
{
	if (m_isInfinite) {
		throw std::logic_error("Cannot concat infinite sequence");
	}
	auto full = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		full->Append(Get(i));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		full->Append(other->Get(i));
	}
	return std::make_unique<LazySequence<T>>(full.get());
}

template <class T>
std::unique_ptr<Sequence<T>>
LazySequence<T>::Map(std::function<T(const T &)> func) const
{
	if (m_isInfinite) {
		throw std::logic_error("Cannot map infinite sequence");
	}
	auto result = std::make_unique<MutableArraySequence<T>>();
	for (int i = 0; i < GetLength(); ++i) {
		result->Append(func(Get(i)));
	}
	return std::make_unique<LazySequence<T>>(result.get());
}

template <class T>
T LazySequence<T>::Reduce(std::function<T(const T &, const T &)> func,
						  T c) const
{
	if (m_isInfinite) {
		throw std::logic_error("Cannot reduce infinite sequence");
	}
	T acc = c;
	for (int i = 0; i < GetLength(); ++i) {
		acc = func(Get(i), acc);
	}
	return acc;
}