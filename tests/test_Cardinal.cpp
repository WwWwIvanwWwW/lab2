#include "Cardinal.hpp"
#include <gtest/gtest.h>

TEST(CardinalTest, DefaultConstructorCreatesInfinite)
{
	Cardinal c;
	EXPECT_TRUE(c.IsInfinite());
}

TEST(CardinalTest, ValueConstructorCreatesFinite)
{
	Cardinal c(42);
	EXPECT_FALSE(c.IsInfinite());
	EXPECT_EQ(c.GetValue(), 42);
}

TEST(CardinalTest, InfinityStaticMethod)
{
	Cardinal c = Cardinal::Infinity();
	EXPECT_TRUE(c.IsInfinite());
}

TEST(CardinalTest, GetValueThrowsOnInfinite)
{
	Cardinal c;
	EXPECT_THROW(c.GetValue(), std::logic_error);
}

TEST(CardinalTest, Equality)
{
	Cardinal c1(5);
	Cardinal c2(5);
	Cardinal c3(10);
	Cardinal inf1 = Cardinal::Infinity();
	Cardinal inf2 = Cardinal::Infinity();

	EXPECT_TRUE(c1 == c2);
	EXPECT_FALSE(c1 == c3);
	EXPECT_TRUE(inf1 == inf2);
	EXPECT_FALSE(c1 == inf1);
}

TEST(CardinalTest, LessThan)
{
	Cardinal c1(5);
	Cardinal c2(10);
	Cardinal inf = Cardinal::Infinity();

	EXPECT_TRUE(c1 < c2);
	EXPECT_TRUE(c1 < inf);
	EXPECT_FALSE(inf < c1);
	EXPECT_FALSE(inf < inf);
}