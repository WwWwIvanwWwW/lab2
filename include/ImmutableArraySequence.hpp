#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <memory>

template <class T> class ImmutableArraySequence : public Sequence<T>
{
  private:
	std::unique_ptr<DynamicArray<T>> m_data;

	void validateIndex(int index) const;

  public:
	ImmutableArraySequence();
	ImmutableArraySequence(T *items, int count);
	ImmutableArraySequence(const DynamicArray<T> &array);
	ImmutableArraySequence(const LinkedList<T> &list);
	ImmutableArraySequence(const ImmutableArraySequence<T> &other);
	ImmutableArraySequence<T> &
	operator=(const ImmutableArraySequence<T> &other);
	ImmutableArraySequence(ImmutableArraySequence<T> &&other) noexcept =
		default;
	ImmutableArraySequence<T> &
	operator=(ImmutableArraySequence<T> &&other) noexcept = default;
	~ImmutableArraySequence() = default;

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

#include "ImmutableArraySequence.tpp"