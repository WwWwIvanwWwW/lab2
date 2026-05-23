#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <memory>

template <class T> class ImmutableListSequence : public Sequence<T>
{
  private:
	std::unique_ptr<LinkedList<T>> m_data;

	void validateIndex(int index) const;

  public:
	ImmutableListSequence();
	ImmutableListSequence(T *items, int count);
	ImmutableListSequence(const LinkedList<T> &list);
	ImmutableListSequence(const DynamicArray<T> &array);
	ImmutableListSequence(const ImmutableListSequence<T> &other);
	ImmutableListSequence<T> &operator=(const ImmutableListSequence<T> &other);
	ImmutableListSequence(ImmutableListSequence<T> &&other) noexcept = default;
	ImmutableListSequence<T> &
	operator=(ImmutableListSequence<T> &&other) noexcept = default;
	~ImmutableListSequence() = default;

	const T &operator[](int index) const;
	T GetFirst() const override;
	T GetLast() const override;
	T Get(int index) const override;
	std::unique_ptr<Sequence<T>> GetSubsequence(int startIndex,
												int endIndex) const override;
	int GetLength() const override;

	void Append(T item) override;
	void Prepend(T item) override;
	void InsertAt(T item, int index) override;
	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override;
};

#include "ImmutableListSequence.tpp"