#include "MutableArraySequence.hpp"
#include "StatisticsCollector.hpp"
#include <gtest/gtest.h>

TEST(StatisticsCollectorTest, AddSingleValue)
{
	StatisticsCollector<int> stats;
	stats.Add(42);

	EXPECT_EQ(stats.GetCount(), 1);
	EXPECT_EQ(stats.GetSum(), 42);
	EXPECT_EQ(stats.GetMin(), 42);
	EXPECT_EQ(stats.GetMax(), 42);
	EXPECT_DOUBLE_EQ(stats.GetMean(), 42.0);
}

TEST(StatisticsCollectorTest, AddMultipleValues)
{
	StatisticsCollector<int> stats;
	stats.Add(10);
	stats.Add(20);
	stats.Add(30);

	EXPECT_EQ(stats.GetCount(), 3);
	EXPECT_EQ(stats.GetSum(), 60);
	EXPECT_EQ(stats.GetMin(), 10);
	EXPECT_EQ(stats.GetMax(), 30);
	EXPECT_DOUBLE_EQ(stats.GetMean(), 20.0);
}

TEST(StatisticsCollectorTest, VarianceAndStdDev)
{
	StatisticsCollector<float> stats;
	stats.Add(2.0);
	stats.Add(4.0);
	stats.Add(4.0);
	stats.Add(4.0);
	stats.Add(5.0);
	stats.Add(5.0);
	stats.Add(7.0);
	stats.Add(9.0);

	EXPECT_DOUBLE_EQ(stats.GetVariance(), 4.0);
	EXPECT_DOUBLE_EQ(stats.GetStdDev(), 2.0);
}

TEST(StatisticsCollectorTest, AddFromSequence)
{
	int arr[] = {1, 2, 3, 4, 5};
	MutableArraySequence<int> seq(arr, 5);
	StatisticsCollector<int> stats;
	stats.Add(&seq);

	EXPECT_EQ(stats.GetCount(), 5);
	EXPECT_EQ(stats.GetSum(), 15);
	EXPECT_DOUBLE_EQ(stats.GetMean(), 3.0);
}

TEST(StatisticsCollectorTest, Reset)
{
	StatisticsCollector<int> stats;
	stats.Add(10);
	stats.Add(20);
	stats.Reset();

	EXPECT_EQ(stats.GetCount(), 0);
	EXPECT_THROW(stats.GetMean(), std::logic_error);
	EXPECT_THROW(stats.GetMin(), std::logic_error);
	EXPECT_THROW(stats.GetMax(), std::logic_error);
}