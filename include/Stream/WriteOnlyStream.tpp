#include "WriteOnlyStream.hpp"

template <class T>
WriteOnlyStream<T>::WriteOnlyStream()
	: m_target(std::make_unique<MutableArraySequence<T>>()), m_position(0),
	  m_isOpen(true)
{
}

template <class T>
WriteOnlyStream<T>::WriteOnlyStream(Sequence<T> *target)
	: m_target(std::make_unique<MutableArraySequence<T>>()), m_position(0),
	  m_isOpen(true)
{
	for (int i = 0; i < target->GetLength(); ++i) {
		m_target->Append(target->Get(i));
	}
}

template <class T> size_t WriteOnlyStream<T>::Write(const T &item)
{
	if (!m_isOpen) {
		throw std::runtime_error("Stream is closed");
	}
	m_target->Append(item);
	++m_position;
	return m_position;
}

template <class T> size_t WriteOnlyStream<T>::GetPosition() const
{
	return m_position;
}

template <class T> void WriteOnlyStream<T>::Open() { m_isOpen = true; }

template <class T> void WriteOnlyStream<T>::Close() { m_isOpen = false; }