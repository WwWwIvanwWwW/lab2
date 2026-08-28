#pragma once

#include <cstddef>
#include <stdexcept>

class Cardinal
{
  public:
	Cardinal();
	explicit Cardinal(size_t value);
	~Cardinal() = default;

	bool IsInfinite() const;
	size_t GetValue() const;

	static Cardinal Infinity();

	bool operator==(const Cardinal &other) const;
	bool operator!=(const Cardinal &other) const;
	bool operator<(const Cardinal &other) const;

  private:
	bool m_isInfinite;
	size_t m_value;
};

#include "Cardinal.tpp"