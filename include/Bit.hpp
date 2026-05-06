#pragma once

#include <iostream>

class Bit
{
  private:
	bool m_value;

  public:
	Bit();
	Bit(bool value);
	Bit(int value);
	Bit(const Bit &other);

	Bit &operator=(bool value);
	Bit &operator=(int value);
	Bit &operator=(const Bit &other);

	bool GetValue() const;
	void SetValue(bool value);

	Bit operator~() const;
	Bit operator&(const Bit &other) const;
	Bit operator|(const Bit &other) const;
	Bit operator^(const Bit &other) const;

	Bit &operator&=(const Bit &other);
	Bit &operator|=(const Bit &other);
	Bit &operator^=(const Bit &other);

	bool operator==(const Bit &other) const;
	bool operator!=(const Bit &other) const;

	explicit operator bool() const;
	explicit operator int() const;

	friend std::ostream &operator<<(std::ostream &os, const Bit &bit);
};