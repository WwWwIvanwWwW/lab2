#pragma once
#include "MutableArraySequence.hpp"
template <class T> class MutableArraySequenceBuilder
{
  private:
	MutableArraySequence<T> m_sequence;

  public:
	void buildAdd(T item) { m_sequence.Append(item); }
	MutableArraySequence<T> build() { return m_sequence; }
};