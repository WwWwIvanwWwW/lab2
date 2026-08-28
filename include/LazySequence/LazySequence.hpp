#pragma once

#include "Cardinal.hpp"
#include "Generator.hpp"
#include "MutableArraySequence.hpp"
#include "Sequence.hpp"
#include <functional>
#include <memory>
#include <stdexcept>

template <class T> class LazySequence : public Sequence<T>
{
  public:
	LazySequence();
	LazySequence(T *items, int count);
	LazySequence(Sequence<T> *seq);
	LazySequence(std::function<T(Sequence<T> *)> func, Sequence<T> *initial);
	LazySequence(const LazySequence<T> &other);
	~LazySequence() = default;

	LazySequence<T> &operator=(const LazySequence<T> &other);
	LazySequence<T> &operator=(LazySequence<T> &&other) noexcept;

	T GetFirst() const override;
	T GetLast() const override;
	T Get(int index) const override;
	std::unique_ptr<Sequence<T>> GetSubsequence(int startIndex,
												int endIndex) const override;
	int GetLength() const override;

	Cardinal GetCardinalLength() const;
	size_t GetMaterializedCount() const;

	void Append(T item) override;
	void Prepend(T item) override;
	void InsertAt(T item, int index) override;
	std::unique_ptr<Sequence<T>> Concat(Sequence<T> *other) const override;

	std::unique_ptr<Sequence<T>>
	Map(std::function<T(const T &)> func) const override;
	T Reduce(std::function<T(const T &, const T &)> func, T c) const override;

  private:
	enum class OpType { Prepend, InsertAt };

	struct Operation {
		OpType type;
		T item;
		int index;
	};

	std::shared_ptr<const LazySequence<T>> m_base;
	std::unique_ptr<Operation> m_op;
	std::unique_ptr<Generator<T>> m_generator;
	mutable std::unique_ptr<MutableArraySequence<T>> m_memo;
	bool m_isInfinite;

	T Compute(int index) const;
	int ComputeLength() const;
	void Materialize(int index) const;
};

#include "LazySequence.tpp"