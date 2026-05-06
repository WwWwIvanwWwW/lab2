#include "Bit.hpp"

Bit::Bit() : m_value(false) {}
Bit::Bit(bool value) : m_value(value) {}
Bit::Bit(int value) : m_value(value != 0) {}
Bit::Bit(const Bit &other) : m_value(other.m_value) {}

Bit &Bit::operator=(bool value)
{
	m_value = value;
	return *this;
}
Bit &Bit::operator=(int value)
{
	m_value = (value != 0);
	return *this;
}
Bit &Bit::operator=(const Bit &other)
{
	m_value = other.m_value;
	return *this;
}

bool Bit::GetValue() const { return m_value; }
void Bit::SetValue(bool value) { m_value = value; }

Bit Bit::operator~() const { return Bit(!m_value); }
Bit Bit::operator&(const Bit &other) const
{
	return Bit(m_value && other.m_value);
}
Bit Bit::operator|(const Bit &other) const
{
	return Bit(m_value || other.m_value);
}
Bit Bit::operator^(const Bit &other) const
{
	return Bit(m_value != other.m_value);
}

Bit &Bit::operator&=(const Bit &other)
{
	m_value = m_value && other.m_value;
	return *this;
}
Bit &Bit::operator|=(const Bit &other)
{
	m_value = m_value || other.m_value;
	return *this;
}
Bit &Bit::operator^=(const Bit &other)
{
	m_value = m_value != other.m_value;
	return *this;
}

bool Bit::operator==(const Bit &other) const
{
	return m_value == other.m_value;
}
bool Bit::operator!=(const Bit &other) const
{
	return m_value != other.m_value;
}

Bit::operator bool() const { return m_value; }
Bit::operator int() const { return m_value ? 1 : 0; }

std::ostream &operator<<(std::ostream &os, const Bit &bit)
{
	os << (bit.m_value ? "1" : "0");
	return os;
}