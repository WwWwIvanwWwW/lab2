#pragma once

#include "ReadOnlyStream.hpp"
#include "Sequence.hpp"
#include <cmath>
#include <stdexcept>

template <class T> class StatisticsCollector
{
  public:
	StatisticsCollector();

	void Add(const T &value);
	void Add(Sequence<T> *seq);
	void Add(ReadOnlyStream<T> *stream);

	size_t GetCount() const;
	T GetSum() const;
	double GetMean() const;
	T GetMin() const;
	T GetMax() const;
	double GetVariance() const;
	double GetStdDev() const;

	void Reset();

  private:
	size_t m_count;
	T m_sum;
	T m_min;
	T m_max;
	T m_m2;
};

#include "StatisticsCollector.tpp"