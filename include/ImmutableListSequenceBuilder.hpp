#pragma once
#include "ImmutableListSequence.hpp"
template <class T> class ImmutableListSequenceBuilder
{
  private:
	ImmutableListSequence<T> m_sequence;

  public:
	void buildAdd(T item) { m_sequence.Append(item); }
	ImmutableListSequence<T> build() { return m_sequence; }
};