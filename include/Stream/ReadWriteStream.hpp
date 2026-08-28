#pragma once

#include "MutableArraySequence.hpp"
#include <memory>
#include <stdexcept>

template <class T> class ReadWriteStream
{
  public:
	ReadWriteStream();
	explicit ReadWriteStream(Sequence<T> *source);
	~ReadWriteStream() = default;

	bool IsEndOfStream() const;
	T Read();
	void Write(const T &item);
	size_t GetPosition() const;
	size_t GetWritePosition() const;

	void Open();
	void Close();

  private:
	std::unique_ptr<MutableArraySequence<T>> m_data;
	size_t m_readPos;
	size_t m_writePos;
	bool m_isOpen;
};

#include "ReadWriteStream.tpp"