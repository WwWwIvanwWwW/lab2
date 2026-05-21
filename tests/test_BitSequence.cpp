#include "Bit.hpp"
#include "BitSequence.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

#define EXPECT_BIT_SEQ(seq, ...)                                               \
	do {                                                                       \
		auto &s = (seq);                                                       \
		int expected[] = {__VA_ARGS__};                                        \
		int expected_size = sizeof(expected) / sizeof(expected[0]);            \
		EXPECT_EQ(s.GetLength(), expected_size)                                \
			<< "Expected length: " << expected_size                            \
			<< ", actual: " << s.GetLength();                                  \
		for (int i = 0; i < expected_size && i < s.GetLength(); ++i) {         \
			EXPECT_EQ(s.Get(i).GetValue(), expected[i])                        \
				<< "At index " << i << ": expected " << expected[i]            \
				<< ", actual " << s.Get(i).GetValue();                         \
		}                                                                      \
	} while (0)

TEST(BitSequenceTest, DefaultConstructor)
{
	BitSequence seq;
	EXPECT_EQ(seq.GetLength(), 0);
}

TEST(BitSequenceTest, ConstructorWithSize)
{
	BitSequence seq(10);
	EXPECT_BIT_SEQ(seq, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

TEST(BitSequenceTest, ConstructorFromArray)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1), Bit(1)};
	BitSequence seq(items, 4);
	EXPECT_BIT_SEQ(seq, 1, 0, 1, 1);
}

TEST(BitSequenceTest, CopyConstructor)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1)};
	BitSequence seq1(items, 3);
	BitSequence seq2(seq1);
	EXPECT_BIT_SEQ(seq2, 1, 0, 1);
}

TEST(BitSequenceTest, MoveConstructor)
{
	Bit items[] = {Bit(1), Bit(0)};
	BitSequence seq1(items, 2);
	BitSequence seq2(std::move(seq1));
	EXPECT_BIT_SEQ(seq2, 1, 0);
	EXPECT_EQ(seq1.GetLength(), 0);
}

TEST(BitSequenceTest, Append)
{
	BitSequence seq;
	seq.Append(Bit(1));
	seq.Append(Bit(0));
	seq.Append(Bit(1));
	EXPECT_BIT_SEQ(seq, 1, 0, 1);
}

TEST(BitSequenceTest, Prepend)
{
	BitSequence seq;
	seq.Prepend(Bit(1));
	seq.Prepend(Bit(0));
	seq.Prepend(Bit(1));
	EXPECT_BIT_SEQ(seq, 1, 0, 1);
}

TEST(BitSequenceTest, InsertAt)
{
	BitSequence seq;
	seq.Append(Bit(1));
	seq.Append(Bit(1));
	seq.InsertAt(Bit(0), 1);
	EXPECT_BIT_SEQ(seq, 1, 0, 1);
}

TEST(BitSequenceTest, GetFirst)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1)};
	BitSequence seq(items, 3);
	EXPECT_EQ(seq.GetFirst().GetValue(), 1);
}

TEST(BitSequenceTest, GetFirstOnEmpty)
{
	BitSequence seq;
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(BitSequenceTest, GetLast)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1)};
	BitSequence seq(items, 3);
	EXPECT_EQ(seq.GetLast().GetValue(), 1);
}

TEST(BitSequenceTest, GetLastOnEmpty)
{
	BitSequence seq;
	EXPECT_THROW(seq.GetLast(), std::out_of_range);
}

TEST(BitSequenceTest, GetSubsequence)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1), Bit(0), Bit(1)};
	BitSequence seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_BIT_SEQ((*sub), 0, 1, 0);
}

TEST(BitSequenceTest, OperatorAnd)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
	Bit items2[] = {Bit(1), Bit(1), Bit(0), Bit(0)};
	BitSequence seq1(items1, 4);
	BitSequence seq2(items2, 4);
	BitSequence result = seq1 & seq2;
	EXPECT_BIT_SEQ(result, 1, 0, 0, 0);
}

TEST(BitSequenceTest, OperatorOr)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
	Bit items2[] = {Bit(1), Bit(1), Bit(0), Bit(0)};
	BitSequence seq1(items1, 4);
	BitSequence seq2(items2, 4);
	BitSequence result = seq1 | seq2;
	EXPECT_BIT_SEQ(result, 1, 1, 1, 0);
}

TEST(BitSequenceTest, OperatorXor)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
	Bit items2[] = {Bit(1), Bit(1), Bit(0), Bit(0)};
	BitSequence seq1(items1, 4);
	BitSequence seq2(items2, 4);
	BitSequence result = seq1 ^ seq2;
	EXPECT_BIT_SEQ(result, 0, 1, 1, 0);
}

TEST(BitSequenceTest, OperatorNot)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
	BitSequence seq(items, 4);
	BitSequence result = ~seq;
	EXPECT_BIT_SEQ(result, 0, 1, 0, 1);
}

TEST(BitSequenceTest, OperatorEqual)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1)};
	Bit items2[] = {Bit(1), Bit(0), Bit(1)};
	BitSequence seq1(items1, 3);
	BitSequence seq2(items2, 3);
	EXPECT_TRUE(seq1 == seq2);
}

TEST(BitSequenceTest, OperatorNotEqual)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1)};
	Bit items2[] = {Bit(1), Bit(1), Bit(0)};
	BitSequence seq1(items1, 3);
	BitSequence seq2(items2, 3);
	EXPECT_TRUE(seq1 != seq2);
}

TEST(BitSequenceTest, SubscriptOperator)
{
	Bit items[] = {Bit(1), Bit(0), Bit(1)};
	BitSequence seq(items, 3);
	EXPECT_BIT_SEQ(seq, 1, 0, 1);
}

TEST(BitSequenceTest, SubscriptOperatorAssign)
{
	BitSequence seq(3);
	seq[0] = Bit(1);
	seq[1] = Bit(0);
	seq[2] = Bit(1);
	EXPECT_BIT_SEQ(seq, 1, 0, 1);
}
TEST(BitSequenceTest, Concat)
{
	Bit items1[] = {Bit(1), Bit(0)};
	Bit items2[] = {Bit(1), Bit(1)};
	BitSequence seq1(items1, 2);
	BitSequence seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_BIT_SEQ((*result), 1, 0, 1, 1);
}

TEST(BitSequenceTest, DifferentLengthBitwiseOperations)
{
	Bit items1[] = {Bit(1), Bit(0), Bit(1)};
	Bit items2[] = {Bit(1), Bit(1)};
	BitSequence seq1(items1, 3);
	BitSequence seq2(items2, 2);
	BitSequence result = seq1 & seq2;
	EXPECT_BIT_SEQ(result, 1, 0, 0);
}