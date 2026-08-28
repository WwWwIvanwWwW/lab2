#pragma once

#include "LazySequence.hpp"
#include "Sequence.hpp"
#include <memory>
#include <stdexcept>

template <class T> class ReadOnlyStream
{
  public:
	ReadOnlyStream();
	explicit ReadOnlyStream(Sequence<T> *source);
	explicit ReadOnlyStream(LazySequence<T> *source);
	~ReadOnlyStream() = default;

	bool IsEndOfStream() const;
	T Read();
	size_t GetPosition() const;
	bool IsCanSeek() const;
	size_t Seek(size_t index);
	bool IsCanGoBack() const;

	void Open();
	void Close();

  private:
	std::unique_ptr<Sequence<T>> m_source;
	size_t m_position;
	bool m_isOpen;
};

#include "ReadOnlyStream.tpp"