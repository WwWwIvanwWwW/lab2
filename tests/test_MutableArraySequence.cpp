#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "MutableArraySequence.hpp"
#include <gtest/gtest.h>

#define EXPECT_MUTABLE_SEQ(seq, ...)                                           \
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

#define EXPECT_MUTABLE_THROW(expression, exception_type)                       \
	EXPECT_THROW(expression, exception_type)

TEST(MutableArraySequenceTest, DefaultConstructor)
{
	MutableArraySequence<int> seq;
	EXPECT_EQ(seq.GetLength(), 0);
	EXPECT_MUTABLE_THROW(seq.GetFirst(), std::out_of_range);
	EXPECT_MUTABLE_THROW(seq.GetLast(), std::out_of_range);
}

TEST(MutableArraySequenceTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq(items, 5);
	EXPECT_MUTABLE_SEQ(seq, 1, 2, 3, 4, 5);
}

TEST(MutableArraySequenceTest, ConstructorFromDynamicArray)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	MutableArraySequence<int> seq(arr);
	EXPECT_MUTABLE_SEQ(seq, 1, 2, 3);
}

TEST(MutableArraySequenceTest, ConstructorFromLinkedList)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	MutableArraySequence<int> seq(list);
	EXPECT_MUTABLE_SEQ(seq, 1, 2, 3);
}

TEST(MutableArraySequenceTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq1(items, 3);
	MutableArraySequence<int> seq2(seq1);

	EXPECT_MUTABLE_SEQ(seq2, 1, 2, 3);

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

	EXPECT_MUTABLE_SEQ(seq2, 1, 2, 3);
}

TEST(MutableArraySequenceTest, GetFirst)
{
	int items[] = {10, 20, 30};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_EQ(seq.GetFirst(), 10);
}

TEST(MutableArraySequenceTest, GetFirstSingleElement)
{
	MutableArraySequence<int> seq;
	seq.Append(42);
	EXPECT_EQ(seq.GetFirst(), 42);
}

TEST(MutableArraySequenceTest, GetFirstOnEmpty)
{
	MutableArraySequence<int> seq;
	EXPECT_MUTABLE_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetLast)
{
	int items[] = {10, 20, 30};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_EQ(seq.GetLast(), 30);
}

TEST(MutableArraySequenceTest, GetLastSingleElement)
{
	MutableArraySequence<int> seq;
	seq.Append(42);
	EXPECT_EQ(seq.GetLast(), 42);
}

TEST(MutableArraySequenceTest, GetLastOnEmpty)
{
	MutableArraySequence<int> seq;
	EXPECT_MUTABLE_THROW(seq.GetLast(), std::out_of_range);
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
	EXPECT_MUTABLE_THROW(seq.Get(-1), std::out_of_range);
	EXPECT_MUTABLE_THROW(seq.Get(3), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetSubsequence)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_MUTABLE_SEQ((*sub), 2, 3, 4);
}

TEST(MutableArraySequenceTest, GetSubsequenceInvalid)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_MUTABLE_THROW(seq.GetSubsequence(-1, 2), std::out_of_range);
	EXPECT_MUTABLE_THROW(seq.GetSubsequence(0, 3), std::out_of_range);
	EXPECT_MUTABLE_THROW(seq.GetSubsequence(2, 1), std::invalid_argument);
}

TEST(MutableArraySequenceTest, Append)
{
	MutableArraySequence<int> seq;
	seq.Append(10);
	seq.Append(20);
	seq.Append(30);
	EXPECT_MUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(MutableArraySequenceTest, Prepend)
{
	MutableArraySequence<int> seq;
	seq.Prepend(30);
	seq.Prepend(20);
	seq.Prepend(10);
	EXPECT_MUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(MutableArraySequenceTest, InsertAt)
{
	int items[] = {10, 30};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(20, 1);
	EXPECT_MUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(MutableArraySequenceTest, InsertAtBeginning)
{
	int items[] = {20, 30};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(10, 0);
	EXPECT_MUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(MutableArraySequenceTest, InsertAtEnd)
{
	int items[] = {10, 20};
	MutableArraySequence<int> seq(items, 2);
	seq.InsertAt(30, 2);
	EXPECT_MUTABLE_SEQ(seq, 10, 20, 30);
}

TEST(MutableArraySequenceTest, InsertAtInvalidIndex)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq(items, 3);
	EXPECT_MUTABLE_THROW(seq.InsertAt(99, -1), std::out_of_range);
	EXPECT_MUTABLE_THROW(seq.InsertAt(99, 4), std::out_of_range);
}

TEST(MutableArraySequenceTest, Concat)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6};
	MutableArraySequence<int> seq1(items1, 3);
	MutableArraySequence<int> seq2(items2, 3);
	auto result = seq1.Concat(&seq2);
	EXPECT_MUTABLE_SEQ((*result), 1, 2, 3, 4, 5, 6);
}

TEST(MutableArraySequenceTest, ConcatWithEmpty)
{
	int items[] = {1, 2, 3};
	MutableArraySequence<int> seq1(items, 3);
	MutableArraySequence<int> seq2;
	auto result = seq1.Concat(&seq2);
	EXPECT_MUTABLE_SEQ((*result), 1, 2, 3);
}

TEST(MutableArraySequenceTest, ConcatBothEmpty)
{
	MutableArraySequence<int> seq1;
	MutableArraySequence<int> seq2;
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 0);
}

TEST(MutableArraySequenceTest, Map)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq1(items, 5);
	auto result = seq1.Map([](int x) { return x * 2; });
	EXPECT_MUTABLE_SEQ(*result, 2, 4, 6, 8, 10);
}

TEST(MutableArraySequenceTest, MapWithEmpty)
{
	MutableArraySequence<int> seq1;
	auto result = seq1.Map([](int x) { return x * 2; });
	EXPECT_EQ(result->GetLength(), 0);
}

TEST(MutableArraySequenceTest, Reduce)
{
	int items[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq1(items, 5);
	auto result = seq1.Reduce([](int x, int acc) { return x + acc; }, 0);
	EXPECT_EQ(result, 15);
}

TEST(MutableArraySequenceTest, ReduceWithEmpty)
{
	MutableArraySequence<int> seq1;
	auto result = seq1.Reduce([](int x, int acc) { return x + acc; }, 0);
	EXPECT_EQ(result, 0);
}

TEST(MutableArraySequenceTestDouble, ConstructorFromArray)
{
	double items[] = {1.1, 2.2, 3.3, 4.4};
	MutableArraySequence<double> seq(items, 4);
	EXPECT_EQ(seq.GetLength(), 4);
	EXPECT_DOUBLE_EQ(seq.Get(0), 1.1);
	EXPECT_DOUBLE_EQ(seq.Get(1), 2.2);
	EXPECT_DOUBLE_EQ(seq.Get(2), 3.3);
	EXPECT_DOUBLE_EQ(seq.Get(3), 4.4);
}

TEST(MutableArraySequenceTestDouble, AppendAndGet)
{
	MutableArraySequence<double> seq;
	seq.Append(1.5);
	seq.Append(2.7);
	seq.Append(3.14);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_DOUBLE_EQ(seq.Get(0), 1.5);
	EXPECT_DOUBLE_EQ(seq.Get(1), 2.7);
	EXPECT_DOUBLE_EQ(seq.Get(2), 3.14);
}

TEST(MutableArraySequenceTestDouble, Prepend)
{
	MutableArraySequence<double> seq;
	seq.Append(2.2);
	seq.Append(3.3);
	seq.Prepend(1.1);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_DOUBLE_EQ(seq.Get(0), 1.1);
	EXPECT_DOUBLE_EQ(seq.Get(1), 2.2);
	EXPECT_DOUBLE_EQ(seq.Get(2), 3.3);
}

TEST(MutableArraySequenceTestDouble, InsertAt)
{
	double items[] = {1.1, 3.3};
	MutableArraySequence<double> seq(items, 2);
	seq.InsertAt(2.2, 1);
	EXPECT_EQ(seq.GetLength(), 3);
	EXPECT_DOUBLE_EQ(seq.Get(0), 1.1);
	EXPECT_DOUBLE_EQ(seq.Get(1), 2.2);
	EXPECT_DOUBLE_EQ(seq.Get(2), 3.3);
}

TEST(MutableArraySequenceTestDouble, GetFirstLast)
{
	double items[] = {1.1, 2.2, 3.3};
	MutableArraySequence<double> seq(items, 3);
	EXPECT_DOUBLE_EQ(seq.GetFirst(), 1.1);
	EXPECT_DOUBLE_EQ(seq.GetLast(), 3.3);
}

TEST(MutableArraySequenceTestDouble, GetSubsequence)
{
	double items[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MutableArraySequence<double> seq(items, 5);
	auto sub = seq.GetSubsequence(1, 3);
	EXPECT_EQ(sub->GetLength(), 3);
	EXPECT_DOUBLE_EQ(sub->Get(0), 2.2);
	EXPECT_DOUBLE_EQ(sub->Get(1), 3.3);
	EXPECT_DOUBLE_EQ(sub->Get(2), 4.4);
}

TEST(MutableArraySequenceTestDouble, Concat)
{
	double items1[] = {1.1, 2.2};
	double items2[] = {3.3, 4.4};
	MutableArraySequence<double> seq1(items1, 2);
	MutableArraySequence<double> seq2(items2, 2);
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 4);
	EXPECT_DOUBLE_EQ(result->Get(0), 1.1);
	EXPECT_DOUBLE_EQ(result->Get(1), 2.2);
	EXPECT_DOUBLE_EQ(result->Get(2), 3.3);
	EXPECT_DOUBLE_EQ(result->Get(3), 4.4);
}

TEST(MutableArraySequenceTestDouble, Map)
{
	double items[] = {1.0, 2.0, 3.0};
	MutableArraySequence<double> seq(items, 3);
	auto result = seq.Map([](const double &x) { return x * 2.0; });
	EXPECT_EQ(result->GetLength(), 3);
	EXPECT_DOUBLE_EQ(result->Get(0), 2.0);
	EXPECT_DOUBLE_EQ(result->Get(1), 4.0);
	EXPECT_DOUBLE_EQ(result->Get(2), 6.0);
}

TEST(MutableArraySequenceTestDouble, Reduce)
{
	double items[] = {1.0, 2.0, 3.0, 4.0};
	MutableArraySequence<double> seq(items, 4);
	double sum = seq.Reduce(
		[](const double &x, const double &acc) { return x + acc; }, 0.0);
	EXPECT_DOUBLE_EQ(sum, 10.0);
}