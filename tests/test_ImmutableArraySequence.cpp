#include "DynamicArray.hpp"
#include "ImmutableArraySequence.hpp"
#include "LinkedList.hpp"
#include <gtest/gtest.h>

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
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(2), 3);
}

TEST(ImmutableArraySequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	ImmutableArraySequence<int> seq(arr);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
}

TEST(ImmutableArraySequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	ImmutableArraySequence<int> seq(list);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
}

TEST(ImmutableArraySequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	ImmutableArraySequence<int> seq1(items, 3);
	ImmutableArraySequence<int> seq2(seq1);
	EXPECT_EQ(seq2.GetLength(), 3);
	EXPECT_EQ(seq2.Get(0), 1);
}

TEST(ImmutableArraySequenceTest, Append)
{
	ImmutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	EXPECT_EQ(seq.GetLength(), 2);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
}

TEST(ImmutableArraySequenceTest, Prepend)
{
	ImmutableArraySequence<int> seq;
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_EQ(seq.GetLength(), 2);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
}

TEST(ImmutableArraySequenceTest, InsertAt)
{
	ImmutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(30);
	seq.InsertAt(20, 1);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(ImmutableArraySequenceTest, Concat)
{
	int items1[] = {1, 2};
	int items2[] = {3, 4};
	ImmutableArraySequence<int> seq1(items1, 2);
	ImmutableArraySequence<int> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 4);
	EXPECT_EQ(result->Get(0), 1);
	EXPECT_EQ(result->Get(2), 3);
}

TEST(ImmutableArraySequenceTest, MultipleOperationsPreserveOriginal)
{
	int items[] = {1, 2, 3};
	ImmutableArraySequence<int> original(items, 3);
	ImmutableArraySequence<int> modified = original;
	modified.Append(4);
	EXPECT_EQ(original.GetLength(), 3);
	EXPECT_EQ(modified.GetLength(), 4);
}