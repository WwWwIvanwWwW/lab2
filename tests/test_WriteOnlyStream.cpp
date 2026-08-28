#include "WriteOnlyStream.hpp"
#include <gtest/gtest.h>

TEST(WriteOnlyStreamTest, WriteAppendsElements)
{
	WriteOnlyStream<int> stream;
	EXPECT_EQ(stream.GetPosition(), 0);

	stream.Write(10);
	EXPECT_EQ(stream.GetPosition(), 1);

	stream.Write(20);
	EXPECT_EQ(stream.GetPosition(), 2);

	stream.Write(30);
	EXPECT_EQ(stream.GetPosition(), 3);
}

TEST(WriteOnlyStreamTest, WriteReturnsNewPosition)
{
	WriteOnlyStream<int> stream;
	EXPECT_EQ(stream.Write(5), 1);
	EXPECT_EQ(stream.Write(10), 2);
	EXPECT_EQ(stream.Write(15), 3);
}

TEST(WriteOnlyStreamTest, ConstructorFromSequenceCopiesElements)
{
	int arr[] = {1, 2, 3};
	MutableArraySequence<int> seq(arr, 3);
	WriteOnlyStream<int> stream(&seq);
	EXPECT_EQ(stream.GetPosition(), 3);

	stream.Write(4);
	EXPECT_EQ(stream.GetPosition(), 4);
}