#pragma once
#include "MutableListSequence.hpp"
template <class T> class MutableListSequenceBuilder
{
  private:
	MutableListSequence<T> m_sequence;

  public:
	void buildAdd(T item) { m_sequence.Append(item); }
	MutableListSequence<T> build() { return m_sequence; }
};