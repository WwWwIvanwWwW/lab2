#pragma once

#include "Bit.hpp"
#include "Sequence.hpp"
#include <memory>
#include <stdexcept>

class BitSequence : public Sequence<Bit>
{
  private:
	std::unique_ptr<uint8_t[]> m_data;
	int m_length;
	static constexpr int BITS_PER_BYTE = 8;

	int bytesCount() const;
	void validateIndex(int index) const;
	void setBit(int index, bool value);
	bool getBit(int index) const;

	class BitProxy
	{
	  private:
		BitSequence &m_seq;
		int m_index;

	  public:
		BitProxy(BitSequence &seq, int index);
		operator Bit() const;
		BitProxy &operator=(const Bit &value);
		BitProxy &operator=(bool value);
		BitProxy &operator=(int value);

		bool operator==(const Bit &other) const
		{
			return m_seq.getBit(m_index) == other.GetValue();
		}

		bool operator!=(const Bit &other) const { return !(*this == other); }
	};
	friend class BitProxy;

  public:
	BitSequence();
	BitSequence(int size);
	BitSequence(Bit *items, int count);
	BitSequence(const BitSequence &other);
	BitSequence(BitSequence &&other) noexcept;
	BitSequence &operator=(const BitSequence &other);
	BitSequence &operator=(BitSequence &&other) noexcept;
	~BitSequence();

	Bit GetFirst() const override;
	Bit GetLast() const override;
	Bit Get(int index) const override;
	std::unique_ptr<Sequence<Bit>> GetSubsequence(int startIndex,
												  int endIndex) const override;
	int GetLength() const override;

	void Append(Bit item) override;
	void Prepend(Bit item) override;
	void InsertAt(Bit item, int index) override;
	std::unique_ptr<Sequence<Bit>> Concat(Sequence<Bit> *other) const override;

	BitSequence operator&(const BitSequence &other) const;
	BitSequence operator|(const BitSequence &other) const;
	BitSequence operator^(const BitSequence &other) const;
	BitSequence operator~() const;

	bool operator==(const BitSequence &other) const;
	bool operator!=(const BitSequence &other) const;

	BitProxy operator[](int index);
	const Bit operator[](int index) const;
};