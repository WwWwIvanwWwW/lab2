#pragma once

#include "ArraySequenceBase.hpp"

template <class T> class MutableArraySequence : public ArraySequenceBase<T>
{
  public:
	using ArraySequenceBase<T>::ArraySequenceBase;
	std::unique_ptr<Sequence<T>> GetSubsequence(int startIndex,
												int endIndex) const override;

	void Append(T item) override;
	void Prepend(T item) override;
	void InsertAt(T item, int index) override;
	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override;

	std::unique_ptr<Sequence<T>>
	Map(std::function<T(const T &)> func) const override;
	T Reduce(std::function<T(const T &, const T &)> func, T c) const override;
};

#include "MutableArraySequence.tpp"