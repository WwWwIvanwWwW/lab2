#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "MutableArraySequence.hpp"
#include <gtest/gtest.h>

TEST(MutableArraySequenceTest, DefaultConstructor)
{
	MutableArraySequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
	EXPECT_THROW(seq.GetLast(), std::out_of_range);
}

TEST(MutableArraySequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq(items, 5);
	EXPECT_EQ(seq.GetLength(), 5);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(4), 5);
}

TEST(MutableArraySequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	MutableArraySequence<int> seq(arr);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(2), 3);
}

TEST(MutableArraySequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	MutableArraySequence<int> seq(list);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(2), 3);
}

TEST(MutableArraySequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq1(items, 3);
	MutableArraySequence<int> seq2(seq1);
	EXPECT_EQ(seq2.GetLength(), 3);
	EXPECT_EQ(seq2.Get(0), 1);
	seq1.Append(100);
	EXPECT_EQ(seq2.GetLength(), 3);
}

TEST(MutableArraySequenceTest, CopyAssignment)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5};
	MutableArraySequence<int> seq1(items1, 3);
	MutableArraySequence<int> seq2(items2, 2);
	seq2 = seq1;
	EXPECT_EQ(seq2.GetLength(), 3);
	EXPECT_EQ(seq2.Get(0), 1);
	EXPECT_EQ(seq2.Get(2), 3);
}

TEST(MutableArraySequenceTest, GetFirst)
{
	int items[] = {10, 20, 30};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_EQ(seq.GetFirst(), 10);
}

TEST(MutableArraySequenceTest, GetFirstOnEmpty)
{
	MutableArraySequence<int> seq;
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetLast)
{
	int items[] = {10, 20, 30};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_EQ(seq.GetLast(), 30);
}

TEST(MutableArraySequenceTest, GetLastOnEmpty)
{
	MutableArraySequence<int> seq;
	EXPECT_THROW(seq.GetLast(), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetValidIndex)
{
	int items[] = {10, 20, 30};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, GetInvalidIndex)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_THROW(seq.Get(-1), std::out_of_range);
	EXPECT_THROW(seq.Get(3), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetSubsequence)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_EQ(sub->GetLength(), 3);
	EXPECT_EQ(sub->Get(0), 2);
	EXPECT_EQ(sub->Get(1), 3);
	EXPECT_EQ(sub->Get(2), 4);
}

TEST(MutableArraySequenceTest, GetSubsequenceInvalid)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_THROW(seq.GetSubsequence(-1, 2), std::out_of_range);
	EXPECT_THROW(seq.GetSubsequence(0, 3), std::out_of_range);
	EXPECT_THROW(seq.GetSubsequence(2, 1), std::invalid_argument);
}

TEST(MutableArraySequenceTest, Append)
{
	MutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	seq.Append(30);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, Prepend)
{
	MutableArraySequence<int> seq;
	seq.Prepend(30);
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, InsertAt)
{
	int items[] = {10, 30};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(20, 1);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, InsertAtBeginning)
{
	int items[] = {20, 30};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(10, 0);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(1), 20);
}

TEST(MutableArraySequenceTest, InsertAtEnd)
{
	int items[] = {10, 20};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(30, 2);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, InsertAtInvalidIndex)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_THROW(seq.InsertAt(99, -1), std::out_of_range);
	EXPECT_THROW(seq.InsertAt(99, 4), std::out_of_range);
}

TEST(MutableArraySequenceTest, Concat)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6};
	MutableArraySequence<int> seq1(items1, 3);
	MutableArraySequence<int> seq2(items2, 3);
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 6);
	EXPECT_EQ(result->Get(0), 1);
	EXPECT_EQ(result->Get(3), 4);
	EXPECT_EQ(result->Get(5), 6);
}

TEST(MutableArraySequenceTest, ConcatWithEmpty)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq1(items, 3);
	MutableArraySequence<int> seq2;
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 3);
}