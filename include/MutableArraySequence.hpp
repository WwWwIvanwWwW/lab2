#pragma once

#include "DynamicArray.hpp"
#include "Sequence.hpp"
#include <memory>

template <class T> class MutableArraySequence : public Sequence<T>
{
  private:
	std::unique_ptr<DynamicArray<T>> m_data;

	void validateIndex(int index) const;

  public:
	MutableArraySequence();
	MutableArraySequence(T *items, int count);
	MutableArraySequence(const DynamicArray<T> &array);
	MutableArraySequence(const LinkedList<T> &list);
	MutableArraySequence(const MutableArraySequence<T> &other);
	MutableArraySequence<T> &operator=(const MutableArraySequence<T> &other);
	MutableArraySequence(MutableArraySequence<T> &&other) noexcept = default;
	MutableArraySequence<T> &
	operator=(MutableArraySequence<T> &&other) noexcept = default;
	~MutableArraySequence() = default;

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

#include "MutableArraySequence.tpp"