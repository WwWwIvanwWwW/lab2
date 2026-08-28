#include "ReadOnlyStream.hpp"

template <class T>
ReadOnlyStream<T>::ReadOnlyStream()
	: m_source(std::make_unique<MutableArraySequence<T>>()), m_position(0),
	  m_isOpen(true)
{
}

template <class T>
ReadOnlyStream<T>::ReadOnlyStream(Sequence<T> *source)
	: m_source(std::make_unique<MutableArraySequence<T>>()), m_position(0),
	  m_isOpen(true)
{
	for (int i = 0; i < source->GetLength(); ++i) {
		static_cast<MutableArraySequence<T> *>(m_source.get())
			->Append(source->Get(i));
	}
}

template <class T>
ReadOnlyStream<T>::ReadOnlyStream(LazySequence<T> *source)
	: m_source(std::make_unique<LazySequence<T>>(*source)), m_position(0),
	  m_isOpen(true)
{
}

template <class T> bool ReadOnlyStream<T>::IsEndOfStream() const
{
	if (!m_isOpen || !m_source)
		return true;
	int len = m_source->GetLength();
	if (len == -1)
		return false;
	return m_position >= static_cast<size_t>(len);
}

template <class T> T ReadOnlyStream<T>::Read()
{
	if (!m_isOpen) {
		throw std::runtime_error("Stream is closed");
	}
	if (IsEndOfStream()) {
		throw std::out_of_range("EndOfStream");
	}
	T value = m_source->Get(m_position);
	++m_position;
	return value;
}

template <class T> size_t ReadOnlyStream<T>::GetPosition() const
{
	return m_position;
}

template <class T> bool ReadOnlyStream<T>::IsCanSeek() const
{
	return m_source != nullptr;
}

template <class T> size_t ReadOnlyStream<T>::Seek(size_t index)
{
	if (!m_isOpen) {
		throw std::runtime_error("Stream is closed");
	}
	if (!IsCanSeek()) {
		throw std::logic_error("Cannot seek in this stream");
	}
	int len = m_source->GetLength();
	if (len == -1) {
		throw std::logic_error("Cannot seek in infinite stream");
	}
	if (index >= static_cast<size_t>(len)) {
		m_position = len;
		return m_position;
	}
	m_position = index;
	return m_position;
}

template <class T> bool ReadOnlyStream<T>::IsCanGoBack() const
{
	return IsCanSeek();
}

template <class T> void ReadOnlyStream<T>::Open() { m_isOpen = true; }

template <class T> void ReadOnlyStream<T>::Close() { m_isOpen = false; }