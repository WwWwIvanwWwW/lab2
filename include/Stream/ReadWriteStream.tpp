#include "ReadWriteStream.hpp"

template <class T>
ReadWriteStream<T>::ReadWriteStream()
	: m_data(std::make_unique<MutableArraySequence<T>>()), m_readPos(0),
	  m_writePos(0), m_isOpen(true)
{
}

template <class T>
ReadWriteStream<T>::ReadWriteStream(Sequence<T> *source)
	: m_data(std::make_unique<MutableArraySequence<T>>()), m_readPos(0),
	  m_writePos(0), m_isOpen(true)
{
	for (int i = 0; i < source->GetLength(); ++i) {
		m_data->Append(source->Get(i));
	}
	m_writePos = m_data->GetLength();
}

template <class T> bool ReadWriteStream<T>::IsEndOfStream() const
{
	if (!m_isOpen)
		return true;
	return m_readPos >= static_cast<size_t>(m_data->GetLength());
}

template <class T> T ReadWriteStream<T>::Read()
{
	if (!m_isOpen) {
		throw std::runtime_error("Stream is closed");
	}
	if (IsEndOfStream()) {
		throw std::out_of_range("EndOfStream");
	}
	T value = m_data->Get(m_readPos);
	++m_readPos;
	return value;
}

template <class T> void ReadWriteStream<T>::Write(const T &item)
{
	if (!m_isOpen) {
		throw std::runtime_error("Stream is closed");
	}
	m_data->Append(item);
	++m_writePos;
}

template <class T> size_t ReadWriteStream<T>::GetPosition() const
{
	return m_readPos;
}

template <class T> size_t ReadWriteStream<T>::GetWritePosition() const
{
	return m_writePos;
}

template <class T> void ReadWriteStream<T>::Open() { m_isOpen = true; }

template <class T> void ReadWriteStream<T>::Close() { m_isOpen = false; }