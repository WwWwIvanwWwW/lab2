#include "Generator.hpp"

template <class T>
Generator<T>::Generator(FuncType func, Sequence<T> *context)
	: m_func(func), m_context(context), m_index(0)
{
}

template <class T> void Generator<T>::SetContext(Sequence<T> *context)
{
	m_context = context;
}

template <class T> T Generator<T>::GetNext()
{
	if (!m_context) {
		throw std::runtime_error("Generator context not set");
	}
	return m_func(m_context);
}

template <class T> bool Generator<T>::HasNext() const { return true; }