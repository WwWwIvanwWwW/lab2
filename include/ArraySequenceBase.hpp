#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include <functional>
#include <memory>

template <class T> class ArraySequenceBase : public Sequence<T>
{
  protected:
	std::unique_ptr<DynamicArray<T>> m_data;

	void validateIndex(int index) const;

  public:
	ArraySequenceBase();
	ArraySequenceBase(T *items, int count);
	ArraySequenceBase(const DynamicArray<T> &array);
	ArraySequenceBase(const LinkedList<T> &list);
	ArraySequenceBase(const ArraySequenceBase<T> &other);
	ArraySequenceBase<T> &operator=(const ArraySequenceBase<T> &other);
	ArraySequenceBase(ArraySequenceBase<T> &&other) noexcept = default;
	ArraySequenceBase<T> &
	operator=(ArraySequenceBase<T> &&other) noexcept = default;
	~ArraySequenceBase() = default;

	const T &operator[](int index) const;
	T GetFirst() const override;
	T GetLast() const override;
	T Get(int index) const override;
	std::unique_ptr<Sequence<T>>
	GetSubsequence(int startIndex, int endIndex) const override = 0;
	int GetLength() const override;
	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override = 0;

	void Append(T item) override = 0;
	void Prepend(T item) override = 0;
	void InsertAt(T item, int index) override = 0;

	std::unique_ptr<Sequence<T>>
	Map(std::function<T(const T &)> func) const override = 0;
	T Reduce(std::function<T(const T &, const T &)> func,
			 T c) const override = 0;
};

#include "ArraySequenceBase.tpp"