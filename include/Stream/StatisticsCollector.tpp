#include "StatisticsCollector.hpp"

template <class T>
StatisticsCollector<T>::StatisticsCollector()
	: m_count(0), m_sum(0), m_min(0), m_max(0), m_m2(0)
{
}

template <class T> void StatisticsCollector<T>::Add(const T &value)
{
	if (m_count == 0) {
		m_min = value;
		m_max = value;
		m_sum = value;
		m_count = 1;
		m_m2 = 0;
		return;
	}

	if (value < m_min)
		m_min = value;
	if (value > m_max)
		m_max = value;

	T oldMean = m_sum / static_cast<T>(m_count);
	m_sum += value;
	++m_count;
	m_m2 += (value - oldMean) * (value - (m_sum / static_cast<T>(m_count)));
}

template <class T> void StatisticsCollector<T>::Add(Sequence<T> *seq)
{
	for (int i = 0; i < seq->GetLength(); ++i) {
		Add(seq->Get(i));
	}
}

template <class T> void StatisticsCollector<T>::Add(ReadOnlyStream<T> *stream)
{
	while (!stream->IsEndOfStream()) {
		Add(stream->Read());
	}
}

template <class T> size_t StatisticsCollector<T>::GetCount() const
{
	return m_count;
}

template <class T> T StatisticsCollector<T>::GetSum() const { return m_sum; }

template <class T> double StatisticsCollector<T>::GetMean() const
{
	if (m_count == 0)
		throw std::logic_error("No data");
	return static_cast<double>(m_sum) / static_cast<double>(m_count);
}

template <class T> T StatisticsCollector<T>::GetMin() const
{
	if (m_count == 0)
		throw std::logic_error("No data");
	return m_min;
}

template <class T> T StatisticsCollector<T>::GetMax() const
{
	if (m_count == 0)
		throw std::logic_error("No data");
	return m_max;
}

template <class T> double StatisticsCollector<T>::GetVariance() const
{
	if (m_count < 2)
		throw std::logic_error("Need at least 2 elements");
	return static_cast<double>(m_m2) / static_cast<double>(m_count);
}

template <class T> double StatisticsCollector<T>::GetStdDev() const
{
	return std::sqrt(GetVariance());
}

template <class T> void StatisticsCollector<T>::Reset()
{
	m_count = 0;
	m_sum = 0;
	m_min = 0;
	m_max = 0;
	m_m2 = 0;
}