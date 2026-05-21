#include "DynamicArray.hpp"
#include "ImmutableListSequence.hpp"
#include "LinkedList.hpp"
#include <gtest/gtest.h>

#define EXPECT_IMMUTABLE_LIST(seq, ...)                                        \
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

TEST(ImmutableListSequenceTest, DefaultConstructor)
{
	ImmutableListSequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(ImmutableListSequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3};
	ImmutableListSequence<int> seq(items, 3);
	EXPECT_IMMUTABLE_LIST(seq, 1, 2, 3);
}

TEST(ImmutableListSequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	ImmutableListSequence<int> seq(list);
	EXPECT_IMMUTABLE_LIST(seq, 1, 2, 3);
}

TEST(ImmutableListSequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	ImmutableListSequence<int> seq(arr);
	EXPECT_IMMUTABLE_LIST(seq, 1, 2, 3);
}

TEST(ImmutableListSequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	ImmutableListSequence<int> seq1(items, 3);
	ImmutableListSequence<int> seq2(seq1);
	EXPECT_IMMUTABLE_LIST(seq2, 1, 2, 3);
}

TEST(ImmutableListSequenceTest, Append)
{
	ImmutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	EXPECT_IMMUTABLE_LIST(seq, 10, 20);
}

TEST(ImmutableListSequenceTest, Prepend)
{
	ImmutableListSequence<int> seq;
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_IMMUTABLE_LIST(seq, 10, 20);
}

TEST(ImmutableListSequenceTest, InsertAt)
{
	ImmutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(30);
	seq.InsertAt(20, 1);
	EXPECT_IMMUTABLE_LIST(seq, 10, 20, 30);
}

TEST(ImmutableListSequenceTest, GetSubsequence)
{
	int items[] = {1, 2, 3, 4, 5};
	ImmutableListSequence<int> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_IMMUTABLE_LIST((*sub), 2, 3, 4);
}

TEST(ImmutableListSequenceTest, Concat)
{
	int items1[] = {1, 2};
	int items2[] = {3, 4};
	ImmutableListSequence<int> seq1(items1, 2);
	ImmutableListSequence<int> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_IMMUTABLE_LIST((*result), 1, 2, 3, 4);
}

TEST(ImmutableListSequenceTest, MultipleOperationsPreserveOriginal)
{
	int items[] = {1, 2, 3};
	ImmutableListSequence<int> original(items, 3);
	ImmutableListSequence<int> modified = original;
	modified.Append(4);
	EXPECT_IMMUTABLE_LIST(original, 1, 2, 3);
	EXPECT_IMMUTABLE_LIST(modified, 1, 2, 3, 4);
}