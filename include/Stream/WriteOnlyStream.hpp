#pragma once

#include "MutableArraySequence.hpp"
#include "Sequence.hpp"
#include <memory>
#include <stdexcept>

template <class T> class WriteOnlyStream
{
  public:
	WriteOnlyStream();
	explicit WriteOnlyStream(Sequence<T> *target);
	~WriteOnlyStream() = default;

	size_t Write(const T &item);
	size_t GetPosition() const;

	void Open();
	void Close();

  private:
	std::unique_ptr<MutableArraySequence<T>> m_target;
	size_t m_position;
	bool m_isOpen;
};

#include "WriteOnlyStream.tpp"