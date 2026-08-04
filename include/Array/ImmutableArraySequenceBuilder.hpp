#pragma once
#include "ImmutableArraySequence.hpp"
template <class T> class ImmutableArraySequenceBuilder
{
  private:
	ImmutableArraySequence<T> m_sequence;

  public:
	void buildAdd(T item) { m_sequence.Append(item); }
	ImmutableArraySequence<T> build() { return m_sequence; }
};