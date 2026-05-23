#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <memory>

template <class T> class MutableListSequence : public Sequence<T>
{
  private:
	std::unique_ptr<LinkedList<T>> m_data;

	void validateIndex(int index) const;

  public:
	MutableListSequence();
	MutableListSequence(T *items, int count);
	MutableListSequence(const LinkedList<T> &list);
	MutableListSequence(const DynamicArray<T> &array);
	MutableListSequence(const MutableListSequence<T> &other);
	MutableListSequence<T> &operator=(const MutableListSequence<T> &other);
	MutableListSequence(MutableListSequence<T> &&other) noexcept = default;
	MutableListSequence<T> &
	operator=(MutableListSequence<T> &&other) noexcept = default;
	~MutableListSequence() = default;

	T &operator[](int index);
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

#include "MutableListSequence.tpp"