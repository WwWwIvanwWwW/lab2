#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <functional>
#include <memory>
#include <stdexcept>

template <class T> class ListSequenceBase : public Sequence<T>
{
  protected:
	std::unique_ptr<LinkedList<T>> m_data;
	void validateIndex(int index) const;

  public:
	ListSequenceBase();
	ListSequenceBase(T *items, int count);
	ListSequenceBase(const LinkedList<T> &list);
	ListSequenceBase(const DynamicArray<T> &array);
	ListSequenceBase(const ListSequenceBase<T> &other);
	ListSequenceBase<T> &operator=(const ListSequenceBase<T> &other);
	ListSequenceBase(ListSequenceBase<T> &&other) noexcept = default;
	ListSequenceBase<T> &
	operator=(ListSequenceBase<T> &&other) noexcept = default;
	~ListSequenceBase() = default;

	T &operator[](int index);
	T GetFirst() const override;
	T GetLast() const override;
	T Get(int index) const override;
	std::unique_ptr<Sequence<T>>
	GetSubsequence(int startIndex, int endIndex) const override = 0;
	int GetLength() const override;

	void Append(T item) override = 0;
	void Prepend(T item) override = 0;
	void InsertAt(T item, int index) override = 0;
	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override = 0;

	std::unique_ptr<Sequence<T>>
	Map(std::function<T(const T &)> func) const override = 0;
	T Reduce(std::function<T(const T &, const T &)> func,
			 T c) const override = 0;
};

#include "ListSequenceBase.tpp"