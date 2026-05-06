#include "BitSequence.hpp"
#include <utility>

BitSequence::BitSequence() : m_data(nullptr), m_length(0) {}

BitSequence::BitSequence(int size) : m_length(size)
{
	if (size < 0) {
		throw std::invalid_argument("size cannot be negative");
	}
	int bytes = bytesCount();
	m_data = std::make_unique<uint8_t[]>(bytes);
	for (int i = 0; i < bytes; ++i) {
		m_data[i] = 0;
	}
}

BitSequence::BitSequence(Bit *items, int count) : m_length(count)
{
	if (count < 0) {
		throw std::invalid_argument("count cannot be negative");
	}
	if (items == nullptr && count > 0) {
		throw std::invalid_argument("items is null but count > 0");
	}
	int bytes = bytesCount();
	m_data = std::make_unique<uint8_t[]>(bytes);
	for (int i = 0; i < bytes; ++i) {
		m_data[i] = 0;
	}
	for (int i = 0; i < count; ++i) {
		if (items[i].GetValue()) {
			setBit(i, true);
		}
	}
}

BitSequence::BitSequence(const BitSequence &other) : m_length(other.m_length)
{
	int bytes = bytesCount();
	m_data = std::make_unique<uint8_t[]>(bytes);
	for (int i = 0; i < bytes; ++i) {
		m_data[i] = other.m_data[i];
	}
}

BitSequence::BitSequence(BitSequence &&other) noexcept
	: m_data(std::move(other.m_data)),
	  m_length(std::exchange(other.m_length, 0))
{
}

BitSequence &BitSequence::operator=(const BitSequence &other)
{
	if (this != &other) {
		m_length = other.m_length;
		int bytes = bytesCount();
		auto newData = std::make_unique<uint8_t[]>(bytes);
		for (int i = 0; i < bytes; ++i) {
			newData[i] = other.m_data[i];
		}
		m_data = std::move(newData);
	}
	return *this;
}

BitSequence &BitSequence::operator=(BitSequence &&other) noexcept
{
	if (this != &other) {
		m_data = std::move(other.m_data);
		m_length = std::exchange(other.m_length, 0);
	}
	return *this;
}

BitSequence::~BitSequence() = default;

int BitSequence::bytesCount() const
{
	return (m_length + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
}

void BitSequence::validateIndex(int index) const
{
	if (index < 0 || index >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
}

void BitSequence::setBit(int index, bool value)
{
	int byteIndex = index / BITS_PER_BYTE;
	int bitOffset = index % BITS_PER_BYTE;
	if (value) {
		m_data[byteIndex] |= (1 << bitOffset);
	} else {
		m_data[byteIndex] &= ~(1 << bitOffset);
	}
}

bool BitSequence::getBit(int index) const
{
	int byteIndex = index / BITS_PER_BYTE;
	int bitOffset = index % BITS_PER_BYTE;
	return (m_data[byteIndex] >> bitOffset) & 1;
}

BitSequence::BitProxy::BitProxy(BitSequence &seq, int index)
	: m_seq(seq), m_index(index)
{
}

BitSequence::BitProxy::operator Bit() const
{
	return Bit(m_seq.getBit(m_index));
}

BitSequence::BitProxy &BitSequence::BitProxy::operator=(const Bit &value)
{
	m_seq.setBit(m_index, value.GetValue());
	return *this;
}

BitSequence::BitProxy &BitSequence::BitProxy::operator=(bool value)
{
	m_seq.setBit(m_index, value);
	return *this;
}

BitSequence::BitProxy &BitSequence::BitProxy::operator=(int value)
{
	m_seq.setBit(m_index, value != 0);
	return *this;
}

Bit BitSequence::GetFirst() const
{
	if (m_length == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return Bit(getBit(0));
}

Bit BitSequence::GetLast() const
{
	if (m_length == 0) {
		throw std::out_of_range("IndexOutOfRange");
	}
	return Bit(getBit(m_length - 1));
}

Bit BitSequence::Get(int index) const
{
	validateIndex(index);
	return Bit(getBit(index));
}

std::unique_ptr<Sequence<Bit>> BitSequence::GetSubsequence(int startIndex,
														   int endIndex) const
{
	if (startIndex < 0 || startIndex >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (endIndex < 0 || endIndex >= m_length) {
		throw std::out_of_range("IndexOutOfRange");
	}
	if (startIndex > endIndex) {
		throw std::invalid_argument(
			"startIndex cannot be greater than endIndex");
	}

	auto subseq = std::make_unique<BitSequence>();
	for (int i = startIndex; i <= endIndex; ++i) {
		subseq->Append(Bit(getBit(i)));
	}
	return subseq;
}

int BitSequence::GetLength() const { return m_length; }

void BitSequence::Append(Bit item)
{
	BitSequence newSeq(m_length + 1);
	for (int i = 0; i < m_length; ++i) {
		if (getBit(i)) {
			newSeq.setBit(i, true);
		}
	}
	newSeq.setBit(m_length, item.GetValue());
	*this = std::move(newSeq);
}

void BitSequence::Prepend(Bit item)
{
	BitSequence newSeq(m_length + 1);
	newSeq.setBit(0, item.GetValue());
	for (int i = 0; i < m_length; ++i) {
		if (getBit(i)) {
			newSeq.setBit(i + 1, true);
		}
	}
	*this = std::move(newSeq);
}

void BitSequence::InsertAt(Bit item, int index)
{
	if (index == 0) {
		Prepend(item);
		return;
	}
	if (index == m_length) {
		Append(item);
		return;
	}

	validateIndex(index);

	BitSequence newSeq(m_length + 1);
	for (int i = 0; i < index; ++i) {
		if (getBit(i)) {
			newSeq.setBit(i, true);
		}
	}
	newSeq.setBit(index, item.GetValue());
	for (int i = index; i < m_length; ++i) {
		if (getBit(i)) {
			newSeq.setBit(i + 1, true);
		}
	}
	*this = std::move(newSeq);
}

std::unique_ptr<Sequence<Bit>> BitSequence::Concat(Sequence<Bit> *other) const
{
	if (other == nullptr) {
		throw std::invalid_argument("other cannot be null");
	}

	auto result = std::make_unique<BitSequence>();
	for (int i = 0; i < m_length; ++i) {
		result->Append(Bit(getBit(i)));
	}
	for (int i = 0; i < other->GetLength(); ++i) {
		result->Append(other->Get(i));
	}
	return result;
}

BitSequence BitSequence::operator&(const BitSequence &other) const
{
	int maxLength = (m_length > other.m_length) ? m_length : other.m_length;
	BitSequence result(maxLength);
	for (int i = 0; i < maxLength; ++i) {
		bool a = (i < m_length) ? getBit(i) : false;
		bool b = (i < other.m_length) ? other.getBit(i) : false;
		result.setBit(i, a && b);
	}
	return result;
}

BitSequence BitSequence::operator|(const BitSequence &other) const
{
	int maxLength = (m_length > other.m_length) ? m_length : other.m_length;
	BitSequence result(maxLength);
	for (int i = 0; i < maxLength; ++i) {
		bool a = (i < m_length) ? getBit(i) : false;
		bool b = (i < other.m_length) ? other.getBit(i) : false;
		result.setBit(i, a || b);
	}
	return result;
}

BitSequence BitSequence::operator^(const BitSequence &other) const
{
	int maxLength = (m_length > other.m_length) ? m_length : other.m_length;
	BitSequence result(maxLength);
	for (int i = 0; i < maxLength; ++i) {
		bool a = (i < m_length) ? getBit(i) : false;
		bool b = (i < other.m_length) ? other.getBit(i) : false;
		result.setBit(i, a != b);
	}
	return result;
}

BitSequence BitSequence::operator~() const
{
	BitSequence result(m_length);
	for (int i = 0; i < m_length; ++i) {
		result.setBit(i, !getBit(i));
	}
	return result;
}

bool BitSequence::operator==(const BitSequence &other) const
{
	if (m_length != other.m_length) {
		return false;
	}
	for (int i = 0; i < m_length; ++i) {
		if (getBit(i) != other.getBit(i)) {
			return false;
		}
	}
	return true;
}

bool BitSequence::operator!=(const BitSequence &other) const
{
	return !(*this == other);
}

BitSequence::BitProxy BitSequence::operator[](int index)
{
	validateIndex(index);
	return BitProxy(*this, index);
}

const Bit BitSequence::operator[](int index) const
{
	validateIndex(index);
	return Bit(getBit(index));
}