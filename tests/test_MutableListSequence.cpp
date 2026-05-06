#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "MutableListSequence.hpp"
#include <gtest/gtest.h>

TEST(MutableListSequenceTest, DefaultConstructor)
{
	MutableListSequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(MutableListSequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3};
	MutableListSequence<int> seq(items, 3);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(2), 3);
}

TEST(MutableListSequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	MutableListSequence<int> seq(list);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
}

TEST(MutableListSequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	MutableListSequence<int> seq(arr);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
}

TEST(MutableListSequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	MutableListSequence<int> seq1(items, 3);
	MutableListSequence<int> seq2(seq1);
	EXPECT_EQ(seq2.GetLength(), 3);
	EXPECT_EQ(seq2.Get(0), 1);
	seq1.Append(100);
	EXPECT_EQ(seq2.GetLength(), 3);
}

TEST(MutableListSequenceTest, Append)
{
	MutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	EXPECT_EQ(seq.GetLength(), 2);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
}

TEST(MutableListSequenceTest, Prepend)
{
	MutableListSequence<int> seq;
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_EQ(seq.GetLength(), 2);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
}

TEST(MutableListSequenceTest, InsertAt)
{
	MutableListSequence<int> seq;
	seq.Append(10);
	seq.Append(30);
	seq.InsertAt(20, 1);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableListSequenceTest, GetSubsequence)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableListSequence<int> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_EQ(sub->GetLength(), 3);
	EXPECT_EQ(sub->Get(0), 2);
	EXPECT_EQ(sub->Get(2), 4);
}

TEST(MutableListSequenceTest, Concat)
{
	int items1[] = {1, 2};
	int items2[] = {3, 4};
	MutableListSequence<int> seq1(items1, 2);
	MutableListSequence<int> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 4);
	EXPECT_EQ(result->Get(0), 1);
	EXPECT_EQ(result->Get(2), 3);
}