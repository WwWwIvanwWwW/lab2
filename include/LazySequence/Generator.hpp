#pragma once

#include "Sequence.hpp"
#include <functional>
#include <memory>
#include <stdexcept>

template <class T> class Generator
{
  public:
	using FuncType = std::function<T(Sequence<T> *)>;

	Generator(FuncType func, Sequence<T> *context = nullptr);
	~Generator() = default;

	void SetContext(Sequence<T> *context);
	T GetNext();
	bool HasNext() const;

  private:
	FuncType m_func;
	Sequence<T> *m_context;
	int m_index;
};

#include "Generator.tpp"