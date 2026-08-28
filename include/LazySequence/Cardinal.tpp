inline Cardinal::Cardinal() : m_isInfinite(true), m_value(0) {}

inline Cardinal::Cardinal(size_t value) : m_isInfinite(false), m_value(value) {}

inline bool Cardinal::IsInfinite() const { return m_isInfinite; }

inline size_t Cardinal::GetValue() const
{
	if (m_isInfinite) {
		throw std::logic_error("Cardinal is infinite");
	}
	return m_value;
}

inline Cardinal Cardinal::Infinity() { return Cardinal(); }

inline bool Cardinal::operator==(const Cardinal &other) const
{
	if (m_isInfinite && other.m_isInfinite)
		return true;
	if (m_isInfinite || other.m_isInfinite)
		return false;
	return m_value == other.m_value;
}

inline bool Cardinal::operator!=(const Cardinal &other) const
{
	return !(*this == other);
}

inline bool Cardinal::operator<(const Cardinal &other) const
{
	if (m_isInfinite)
		return false;
	if (other.m_isInfinite)
		return true;
	return m_value < other.m_value;
}