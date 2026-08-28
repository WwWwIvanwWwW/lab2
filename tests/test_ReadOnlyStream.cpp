#include "MutableArraySequence.hpp"
#include "ReadOnlyStream.hpp"
#include <gtest/gtest.h>

TEST(ReadOnlyStreamTest, ReadReturnsElementsInOrder)
{
	int arr[] = {10, 20, 30, 40};
	MutableArraySequence<int> seq(arr, 4);
	ReadOnlyStream<int> stream(&seq);

	EXPECT_FALSE(stream.IsEndOfStream());
	EXPECT_EQ(stream.GetPosition(), 0);

	EXPECT_EQ(stream.Read(), 10);
	EXPECT_EQ(stream.GetPosition(), 1);

	EXPECT_EQ(stream.Read(), 20);
	EXPECT_EQ(stream.GetPosition(), 2);

	EXPECT_EQ(stream.Read(), 30);
	EXPECT_EQ(stream.GetPosition(), 3);

	EXPECT_EQ(stream.Read(), 40);
	EXPECT_EQ(stream.GetPosition(), 4);

	EXPECT_TRUE(stream.IsEndOfStream());
}

TEST(ReadOnlyStreamTest, ReadThrowsWhenEndOfStream)
{
	int arr[] = {1, 2};
	MutableArraySequence<int> seq(arr, 2);
	ReadOnlyStream<int> stream(&seq);

	stream.Read();
	stream.Read();
	EXPECT_THROW(stream.Read(), std::out_of_range);
}

TEST(ReadOnlyStreamTest, SeekMovesPosition)
{
	int arr[] = {100, 200, 300, 400, 500};
	MutableArraySequence<int> seq(arr, 5);
	ReadOnlyStream<int> stream(&seq);

	stream.Seek(3);
	EXPECT_EQ(stream.GetPosition(), 3);
	EXPECT_EQ(stream.Read(), 400);
}

TEST(ReadOnlyStreamTest, SeekBeyondEndSetsPositionToEnd)
{
	int arr[] = {1, 2, 3};
	MutableArraySequence<int> seq(arr, 3);
	ReadOnlyStream<int> stream(&seq);

	size_t pos = stream.Seek(10);
	EXPECT_EQ(pos, 3);
	EXPECT_TRUE(stream.IsEndOfStream());
}