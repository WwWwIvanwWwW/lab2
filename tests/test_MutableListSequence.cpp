#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "MutableListSequence.hpp"
#include <gtest/gtest.h>

#define EXPECT_MUTABLE_LIST(seq, ...)                                          \
	do {                                                                       \
		auto &s = (seq);                                                       \
		int expected[] = {__VA_ARGS__};                                        \
		int expected_size = sizeof(expected) / sizeof(expected[0]);            \
		EXPECT_EQ(s.GetLength(), expected_size)                                \
			<< "Expected length: " << expected_size                            \
			<< ", actual: " << s.GetLength();                                  \
		for (int i = 0; i < expected_size && i < s.GetLength(); ++i) {         \
			EXPECT_EQ(s.Get(i), expected[i])                                   \
				<< "At index " << i << ": expected " << expected[i]            \
				<< ", actual " << s.Get(i);                                    \
		}                                                                      \
	} while (0)

#define EXPECT_MUTABLE_LIST_THROW(expression, exception_type)                  \
	EXPECT_THROW(expression, exception_type)

TEST(MutableListSequenceTest, DefaultConstructor)
{
	MutableListSequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_MUTABLE_LIST_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(MutableListSequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3};
	MutableListSequence<int> seq(items, 3);
	EXPECT_MUTABLE_LIST(seq, 1, 2, 3);
}

TEST(MutableListSequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	MutableListSequence<int> seq(list);
	EXPECT_MUTABLE_LIST(seq, 1, 2, 3);
}

TEST(MutableListSequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	MutableListSequence<int> seq(arr);
	EXPECT_MUTABLE_LIST(seq, 1, 2, 3);
}

TEST(MutableListSequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	MutableListSequence<int> seq1(items, 3);
	MutableListSequence<int> seq2(seq1);

	EXPECT_MUTABLE_LIST(seq2, 1, 2, 3);

	seq1.Append(100);
	EXPECT_EQ(seq2.GetLength(), 3);
}

TEST(MutableListSequenceTest, Append)
{
	MutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	EXPECT_MUTABLE_LIST(seq, 10, 20);
}

TEST(MutableListSequenceTest, Prepend)
{
	MutableListSequence<int> seq;
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_MUTABLE_LIST(seq, 10, 20);
}

TEST(MutableListSequenceTest, InsertAt)
{
	MutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(30);
	seq.InsertAt(20, 1);
	EXPECT_MUTABLE_LIST(seq, 10, 20, 30);
}

TEST(MutableListSequenceTest, GetSubsequence)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableListSequence<int> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_MUTABLE_LIST((*sub), 2, 3, 4);
}

TEST(MutableListSequenceTest, GetSubsequenceWithEmpty)
{
	MutableListSequence<int> seq;
	EXPECT_MUTABLE_LIST_THROW(seq.GetSubsequence(0, 0), std::out_of_range);
}

TEST(MutableListSequenceTest, Concat)
{
	int items1[] = {1, 2};
	int items2[] = {3, 4};
	MutableListSequence<int> seq1(items1, 2);
	MutableListSequence<int> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_MUTABLE_LIST((*result), 1, 2, 3, 4);
}