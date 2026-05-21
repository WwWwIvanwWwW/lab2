#pragma once
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

template <typename T> std::string SeqToString(Sequence<T> *seq)
{
	if (!seq)
		return "nullptr";
	if (seq->GetLength() == 0)
		return "[]";

	std::ostringstream oss;
	oss << "[";
	for (int i = 0; i < seq->GetLength(); ++i) {
		oss << seq->Get(i);
		if (i + 1 < seq->GetLength())
			oss << ", ";
	}
	oss << "]";
	return oss.str();
}

template <typename T>
std::string SeqToString(const std::unique_ptr<Sequence<T>> &seq)
{
	return SeqToString(seq.get());
}

inline std::string BitToString(const Bit &b)
{
	return b.GetValue() ? "1" : "0";
}

template <> inline std::string SeqToString<Bit>(Sequence<Bit> *seq)
{
	if (!seq)
		return "nullptr";
	if (seq->GetLength() == 0)
		return "[]";

	std::ostringstream oss;
	oss << "[";
	for (int i = 0; i < seq->GetLength(); ++i) {
		oss << (seq->Get(i).GetValue() ? "1" : "0");
		if (i + 1 < seq->GetLength())
			oss << ", ";
	}
	oss << "]";
	return oss.str();
}

#define EXPECT_SEQ_EQ(seq, expected_values)                                    \
	do {                                                                       \
		auto *s = (seq);                                                       \
		auto expected = (expected_values);                                     \
		EXPECT_EQ(s->GetLength(), (int)expected.size())                        \
			<< "Expected length: " << expected.size()                          \
			<< ", actual: " << s->GetLength()                                  \
			<< "\nExpected sequence: " << ::testing::PrintToString(expected)   \
			<< "\nActual sequence  : " << SeqToString(s);                      \
		for (int i = 0; i < (int)expected.size() && i < s->GetLength(); ++i) { \
			EXPECT_EQ(s->Get(i), expected[i])                                  \
				<< "At index " << i << "\nExpected: " << expected[i]           \
				<< "\nActual  : " << s->Get(i);                                \
		}                                                                      \
	} while (0)

#define EXPECT_BITSEQ_EQ(seq, expected_bits)                                   \
	do {                                                                       \
		auto *s = (seq);                                                       \
		auto expected = (expected_bits);                                       \
		EXPECT_EQ(s->GetLength(), (int)expected.size())                        \
			<< "Expected length: " << expected.size()                          \
			<< ", actual: " << s->GetLength()                                  \
			<< "\nExpected bits: " << ::testing::PrintToString(expected)       \
			<< "\nActual bits  : " << SeqToString(s);                          \
		for (int i = 0; i < (int)expected.size() && i < s->GetLength(); ++i) { \
			EXPECT_EQ(s->Get(i).GetValue(), expected[i])                       \
				<< "At index " << i                                            \
				<< "\nExpected: " << (expected[i] ? "1" : "0")                 \
				<< "\nActual  : " << (s->Get(i).GetValue() ? "1" : "0");       \
		}                                                                      \
	} while (0)