#include "Generator.hpp"
#include "MutableArraySequence.hpp"
#include <gtest/gtest.h>

TEST(GeneratorTest, GetNextReturnsSequentialValues)
{
	int counter = 0;
	auto func = [&counter](Sequence<int> *) -> int { return ++counter; };

	MutableArraySequence<int> dummy;
	Generator<int> gen(func, &dummy);

	EXPECT_EQ(gen.GetNext(), 1);
	EXPECT_EQ(gen.GetNext(), 2);
	EXPECT_EQ(gen.GetNext(), 3);
}

TEST(GeneratorTest, HasNextAlwaysTrueForInfinite)
{
	auto func = [](Sequence<int> *) -> int { return 42; };

	MutableArraySequence<int> dummy;
	Generator<int> gen(func, &dummy);

	EXPECT_TRUE(gen.HasNext());
	gen.GetNext();
	EXPECT_TRUE(gen.HasNext());
	gen.GetNext();
	gen.GetNext();
	EXPECT_TRUE(gen.HasNext());
}