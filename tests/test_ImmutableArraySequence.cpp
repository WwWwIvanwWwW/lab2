#include "DynamicArray.hpp"
#include "ImmutableArraySequence.hpp"
#include "LinkedList.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

#define EXPECT_IMMUTABLE_SEQ(seq, ...)                                         \
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

TEST(ImmutableArraySequenceTest, DefaultConstructor)
{
	ImmutableArraySequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(ImmutableArraySequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3};
	ImmutableArraySequence<int> seq(items, 3);
	EXPECT_IMMUTABLE_SEQ(seq, 1, 2, 3);
}

TEST(ImmutableArraySequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	ImmutableArraySequence<int> seq(arr);
	EXPECT_IMMUTABLE_SEQ(seq, 1, 2, 3);
}

TEST(ImmutableArraySequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	ImmutableArraySequence<int> seq(list);
	EXPECT_IMMUTABLE_SEQ(seq, 1, 2, 3);
}

TEST(ImmutableArraySequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	ImmutableArraySequence<int> seq1(items, 3);
	ImmutableArraySequence<int> seq2(seq1);
	EXPECT_IMMUTABLE_SEQ(seq2, 1, 2, 3);
}

TEST(ImmutableArraySequenceTest, Append)
{
	ImmutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	EXPECT_IMMUTABLE_SEQ(seq, 10, 20);
}

TEST(ImmutableArraySequenceTest, Prepend)
{
	ImmutableArraySequence<int> seq;
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_IMMUTABLE_SEQ(seq, 10, 20);
}

TEST(ImmutableArraySequenceTest, InsertAt)
{
	ImmutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(30);
	seq.InsertAt(20, 1);
	EXPECT_IMMUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(ImmutableArraySequenceTest, Concat)
{
	int items1[] = {1, 2};
	int items2[] = {3, 4};
	ImmutableArraySequence<int> seq1(items1, 2);
	ImmutableArraySequence<int> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_IMMUTABLE_SEQ((*result), 1, 2, 3, 4);
}

TEST(ImmutableArraySequenceTest, MultipleOperationsPreserveOriginal)
{
	int items[] = {1, 2, 3};
	ImmutableArraySequence<int> original(items, 3);
	ImmutableArraySequence<int> modified = original;
	modified.Append(4);
	EXPECT_IMMUTABLE_SEQ(original, 1, 2, 3);
	EXPECT_IMMUTABLE_SEQ(modified, 1, 2, 3, 4);
}