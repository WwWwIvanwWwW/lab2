#include "LazySequence.hpp"
#include "MutableArraySequence.hpp"
#include <gtest/gtest.h>
#include <limits>

TEST(LazySequenceTest, DefaultConstructorCreatesEmpty)
{
	LazySequence<int> seq;
	EXPECT_EQ(seq.GetMaterializedCount(), 0);
	EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(LazySequenceTest, ConstructorFromArray)
{
	int arr[] = {1, 2, 3, 4, 5};
	LazySequence<int> seq(arr, 5);
	EXPECT_EQ(seq.GetMaterializedCount(), 5);
	EXPECT_EQ(seq.GetFirst(), 1);
	EXPECT_EQ(seq.GetLast(), 5);
	EXPECT_EQ(seq.Get(2), 3);
}

TEST(LazySequenceTest, ConstructorFromSequence)
{
	int arr[] = {10, 20, 30};
	MutableArraySequence<int> source(arr, 3);
	LazySequence<int> seq(&source);
	EXPECT_EQ(seq.GetMaterializedCount(), 3);
	EXPECT_EQ(seq.Get(0), 10);
	EXPECT_EQ(seq.Get(2), 30);
}

TEST(LazySequenceTest, ConstructorWithGenerator)
{
	auto generator = [](Sequence<int> *seq) -> int {
		auto *lazy = dynamic_cast<LazySequence<int> *>(seq);
		if (!lazy)
			throw std::runtime_error("Invalid context");
		int len = lazy->GetMaterializedCount();
		if (len == 0)
			return 1;
		if (len == 1)
			return 1;
		return lazy->Get(len - 1) + lazy->Get(len - 2);
	};
	int initial[] = {1, 1};
	MutableArraySequence<int> initialSeq(initial, 2);
	LazySequence<int> seq(generator, &initialSeq);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(seq.Get(1), 1);
	EXPECT_EQ(seq.Get(2), 2);
	EXPECT_EQ(seq.Get(3), 3);
	EXPECT_EQ(seq.Get(4), 5);
	EXPECT_EQ(seq.Get(5), 8);
}

TEST(LazySequenceTest, GetThrowsOnNegativeIndex)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq(arr, 3);
	EXPECT_THROW(seq.Get(-1), std::out_of_range);
}

TEST(LazySequenceTest, GetLastThrowsOnEmpty)
{
	LazySequence<int> seq;
	EXPECT_THROW(seq.GetLast(), std::out_of_range);
}

TEST(LazySequenceTest, GetLengthForInfiniteReturnsMinusOne)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	EXPECT_EQ(seq.GetLength(), -1);
}

TEST(LazySequenceTest, GetCardinalLengthForInfiniteReturnsInfinity)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	Cardinal len = seq.GetCardinalLength();
	EXPECT_TRUE(len.IsInfinite());
}

TEST(LazySequenceTest, GetCardinalLengthForFiniteReturnsValue)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq(arr, 3);
	Cardinal len = seq.GetCardinalLength();
	EXPECT_FALSE(len.IsInfinite());
	EXPECT_EQ(len.GetValue(), 3);
}

TEST(LazySequenceTest, GetSubsequenceFinite)
{
	int arr[] = {0, 1, 2, 3, 4, 5};
	LazySequence<int> seq(arr, 6);
	auto sub = seq.GetSubsequence(2, 4);
	EXPECT_EQ(sub->GetLength(), 3);
	EXPECT_EQ(sub->Get(0), 2);
	EXPECT_EQ(sub->Get(1), 3);
	EXPECT_EQ(sub->Get(2), 4);
}

TEST(LazySequenceTest, GetSubsequenceThrowsOnInvalidIndices)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq(arr, 3);
	EXPECT_THROW(seq.GetSubsequence(-1, 2), std::invalid_argument);
	EXPECT_THROW(seq.GetSubsequence(2, 1), std::invalid_argument);
}

TEST(LazySequenceTest, AppendModifiesCurrentObject)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq(arr, 3);
	LazySequence<int> oldSeq = seq;
	seq.Append(4);
	EXPECT_EQ(seq.GetLength(), 4);
	EXPECT_EQ(seq.Get(3), 4);
	EXPECT_EQ(oldSeq.GetLength(), 3);
	EXPECT_EQ(oldSeq.Get(2), 3);
}

TEST(LazySequenceTest, PrependModifiesCurrentObject)
{
	int arr[] = {2, 3, 4};
	LazySequence<int> seq(arr, 3);
	LazySequence<int> oldSeq = seq;
	seq.Prepend(1);
	EXPECT_EQ(seq.GetLength(), 4);
	EXPECT_EQ(seq.Get(0), 1);
	EXPECT_EQ(oldSeq.GetLength(), 3);
	EXPECT_EQ(oldSeq.Get(0), 2);
}

TEST(LazySequenceTest, InsertAtModifiesCurrentObject)
{
	int arr[] = {1, 2, 4};
	LazySequence<int> seq(arr, 3);
	LazySequence<int> oldSeq = seq;
	seq.InsertAt(3, 2);
	EXPECT_EQ(seq.GetLength(), 4);
	EXPECT_EQ(seq.Get(2), 3);
	EXPECT_EQ(oldSeq.GetLength(), 3);
	EXPECT_EQ(oldSeq.Get(2), 4);
}

TEST(LazySequenceTest, AppendThrowsForInfinite)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	EXPECT_THROW(seq.Append(42), std::logic_error);
}

TEST(LazySequenceTest, ConcatThrowsForInfinite)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	int arr[] = {1, 2, 3};
	MutableArraySequence<int> other(arr, 3);
	EXPECT_THROW(seq.Concat(&other), std::logic_error);
}

TEST(LazySequenceTest, ConcatForFinite)
{
	int arr1[] = {1, 2, 3};
	int arr2[] = {4, 5, 6};
	LazySequence<int> seq1(arr1, 3);
	MutableArraySequence<int> seq2(arr2, 3);
	auto result = seq1.Concat(&seq2);
	EXPECT_EQ(result->GetLength(), 6);
	EXPECT_EQ(result->Get(0), 1);
	EXPECT_EQ(result->Get(3), 4);
	EXPECT_EQ(result->Get(5), 6);
}

TEST(LazySequenceTest, MapForFinite)
{
	int arr[] = {1, 2, 3, 4, 5};
	LazySequence<int> seq(arr, 5);
	auto result = seq.Map([](const int &x) { return x * 2; });
	EXPECT_EQ(result->GetLength(), 5);
	EXPECT_EQ(result->Get(0), 2);
	EXPECT_EQ(result->Get(2), 6);
	EXPECT_EQ(result->Get(4), 10);
}

TEST(LazySequenceTest, MapThrowsForInfinite)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	EXPECT_THROW(seq.Map([](const int &x) { return x * 2; }), std::logic_error);
}

TEST(LazySequenceTest, ReduceForFinite)
{
	int arr[] = {1, 2, 3, 4, 5};
	LazySequence<int> seq(arr, 5);
	int sum =
		seq.Reduce([](const int &x, const int &acc) { return x + acc; }, 0);
	EXPECT_EQ(sum, 15);
}

TEST(LazySequenceTest, ReduceThrowsForInfinite)
{
	auto generator = [](Sequence<int> *seq) -> int {
		return seq->GetLength() + 1;
	};
	LazySequence<int> seq(generator, nullptr);
	EXPECT_THROW(
		seq.Reduce([](const int &x, const int &acc) { return x + acc; }, 0),
		std::logic_error);
}

TEST(LazySequenceTest, CopyConstructor)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq1(arr, 3);
	LazySequence<int> seq2(seq1);
	EXPECT_EQ(seq2.GetMaterializedCount(), 3);
	EXPECT_EQ(seq2.Get(0), 1);
	EXPECT_EQ(seq2.Get(2), 3);
	seq1.Append(4);
	EXPECT_EQ(seq1.GetLength(), 4);
	EXPECT_EQ(seq2.GetLength(), 3);
}

TEST(LazySequenceTest, MultipleOperations)
{
	int arr[] = {1, 2, 3};
	LazySequence<int> seq(arr, 3);
	seq.Append(4);
	seq.Prepend(0);
	seq.InsertAt(99, 3);
	EXPECT_EQ(seq.GetLength(), 6);
	EXPECT_EQ(seq.Get(0), 0);
	EXPECT_EQ(seq.Get(1), 1);
	EXPECT_EQ(seq.Get(2), 2);
	EXPECT_EQ(seq.Get(3), 99);
	EXPECT_EQ(seq.Get(4), 3);
	EXPECT_EQ(seq.Get(5), 4);
}

TEST(LazySequenceTestDouble, ConstructorFromArray)
{
	double arr[] = {1.1, 2.2, 3.3};
	LazySequence<double> seq(arr, 3);
	EXPECT_EQ(seq.GetMaterializedCount(), 3);
	EXPECT_DOUBLE_EQ(seq.GetFirst(), 1.1);
	EXPECT_DOUBLE_EQ(seq.GetLast(), 3.3);
	EXPECT_DOUBLE_EQ(seq.Get(1), 2.2);
}

TEST(LazySequenceTestDouble, ConstructorWithGenerator)
{
	auto generator = [](Sequence<double> *seq) -> double {
		auto *lazy = dynamic_cast<LazySequence<double> *>(seq);
		if (!lazy)
			throw std::runtime_error("Invalid context");
		int len = lazy->GetMaterializedCount();
		if (len == 0)
			return 1.0;
		if (len == 1)
			return 1.0;
		return lazy->Get(len - 1) + lazy->Get(len - 2);
	};
	double initial[] = {1.0, 1.0};
	MutableArraySequence<double> initialSeq(initial, 2);
	LazySequence<double> seq(generator, &initialSeq);
	EXPECT_DOUBLE_EQ(seq.Get(0), 1.0);
	EXPECT_DOUBLE_EQ(seq.Get(1), 1.0);
	EXPECT_DOUBLE_EQ(seq.Get(2), 2.0);
	EXPECT_DOUBLE_EQ(seq.Get(3), 3.0);
	EXPECT_DOUBLE_EQ(seq.Get(4), 5.0);
}

TEST(LazySequenceTestDouble, Append)
{
	double arr[] = {1.1, 2.2, 3.3};
	LazySequence<double> seq(arr, 3);
	seq.Append(4.4);
	EXPECT_EQ(seq.GetLength(), 4);
	EXPECT_DOUBLE_EQ(seq.Get(3), 4.4);
}

TEST(LazySequenceTestDouble, Map)
{
	double arr[] = {1.0, 2.0, 3.0};
	LazySequence<double> seq(arr, 3);
	auto result = seq.Map([](const double &x) { return x * 2.0; });
	EXPECT_EQ(result->GetLength(), 3);
	EXPECT_DOUBLE_EQ(result->Get(0), 2.0);
	EXPECT_DOUBLE_EQ(result->Get(1), 4.0);
	EXPECT_DOUBLE_EQ(result->Get(2), 6.0);
}

TEST(LazySequenceTestDouble, Reduce)
{
	double arr[] = {1.0, 2.0, 3.0, 4.0};
	LazySequence<double> seq(arr, 4);
	double sum = seq.Reduce(
		[](const double &x, const double &acc) { return x + acc; }, 0.0);
	EXPECT_DOUBLE_EQ(sum, 10.0);
}