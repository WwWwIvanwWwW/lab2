#include "DynamicArray.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

#define EXPECT_ARRAY(arr, ...)                                                 \
	do {                                                                       \
		auto &a = (arr);                                                       \
		int expected[] = {__VA_ARGS__};                                        \
		int expected_size = sizeof(expected) / sizeof(expected[0]);            \
		EXPECT_EQ(a.GetSize(), expected_size)                                  \
			<< "Expected size: " << expected_size                              \
			<< ", actual: " << a.GetSize();                                    \
		for (int i = 0; i < expected_size && i < a.GetSize(); ++i) {           \
			EXPECT_EQ(a.Get(i), expected[i])                                   \
				<< "At index " << i << ": expected " << expected[i]            \
				<< ", actual " << a.Get(i);                                    \
		}                                                                      \
	} while (0)

#define EXPECT_ARRAY_THROW(expression, exception_type)                         \
	EXPECT_THROW(expression, exception_type)

TEST(DynamicArrayTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3, 4, 5};
	DynamicArray<int> arr(items, 5);
	EXPECT_ARRAY(arr, 1, 2, 3, 4, 5);
}

TEST(DynamicArrayTest, ConstructorFromArrayWithNullptr)
{
	EXPECT_ARRAY_THROW(DynamicArray<int> arr(nullptr, 5),
					   std::invalid_argument);
}

TEST(DynamicArrayTest, ConstructorFromArrayWithNegativeCount)
{
	int items[] = {1, 2, 3};
	EXPECT_ARRAY_THROW(DynamicArray<int> arr(items, -1), std::invalid_argument);
}

TEST(DynamicArrayTest, ConstructorFromArrayWithNullptrAndNegativeCount)
{
	EXPECT_ARRAY_THROW(DynamicArray<int> arr(nullptr, -1),
					   std::invalid_argument);
}

TEST(DynamicArrayTest, ConstructorWithSize)
{
	DynamicArray<int> arr(10);
	EXPECT_ARRAY(arr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

TEST(DynamicArrayTest, ConstructorWithNegativeSize)
{
	EXPECT_ARRAY_THROW(DynamicArray<int> arr(-5), std::invalid_argument);
}

TEST(DynamicArrayTest, ConstructorWithZeroSize)
{
	DynamicArray<int> arr(0);
	EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr1(items, 3);
	DynamicArray<int> arr2(arr1);

	EXPECT_ARRAY(arr2, 1, 2, 3);

	arr1.Set(0, 100);
	EXPECT_EQ(arr2.Get(0), 1);
}

TEST(DynamicArrayTest, CopyAssignmentOperator)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6, 7};
	DynamicArray<int> arr1(items1, 3);
	DynamicArray<int> arr2(items2, 4);

	arr2 = arr1;

	EXPECT_ARRAY(arr2, 1, 2, 3);
	EXPECT_ARRAY_THROW(arr2.Get(3), std::out_of_range);
}

TEST(DynamicArrayTest, MoveConstructor)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr1(items, 3);
	DynamicArray<int> arr2(std::move(arr1));

	EXPECT_ARRAY(arr2, 1, 2, 3);
	EXPECT_EQ(arr1.GetSize(), 0);
}

TEST(DynamicArrayTest, MoveAssignmentOperator)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5};
	DynamicArray<int> arr1(items1, 3);
	DynamicArray<int> arr2(items2, 2);

	arr2 = std::move(arr1);

	EXPECT_ARRAY(arr2, 1, 2, 3);
	EXPECT_EQ(arr1.GetSize(), 0);
}

TEST(DynamicArrayTest, GetInvalidIndex)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	EXPECT_ARRAY_THROW(arr.Get(-1), std::out_of_range);
	EXPECT_ARRAY_THROW(arr.Get(3), std::out_of_range);
	EXPECT_ARRAY_THROW(arr.Get(100), std::out_of_range);
}

TEST(DynamicArrayTest, SetValidIndex)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	arr.Set(1, 100);
	EXPECT_EQ(arr.Get(1), 100);

	arr.Set(0, 50);
	EXPECT_EQ(arr.Get(0), 50);
}

TEST(DynamicArrayTest, SetInvalidIndex)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	EXPECT_ARRAY_THROW(arr.Set(-1, 10), std::out_of_range);
	EXPECT_ARRAY_THROW(arr.Set(3, 10), std::out_of_range);
}

TEST(DynamicArrayTest, ResizeIncrease)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	arr.Resize(5);

	EXPECT_ARRAY(arr, 1, 2, 3, 0, 0);
}

TEST(DynamicArrayTest, ResizeDecrease)
{
	int items[] = {1, 2, 3, 4, 5};
	DynamicArray<int> arr(items, 5);

	arr.Resize(3);

	EXPECT_ARRAY(arr, 1, 2, 3);
}

TEST(DynamicArrayTest, ResizeToSameSize)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	arr.Resize(3);

	EXPECT_ARRAY(arr, 1, 2, 3);
}

TEST(DynamicArrayTest, ResizeToZero)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);

	arr.Resize(0);

	EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, ResizeNegative)
{
	DynamicArray<int> arr(5);
	EXPECT_ARRAY_THROW(arr.Resize(-10), std::invalid_argument);
}

TEST(DynamicArrayTest, GetSizeOnEmptyArray)
{
	DynamicArray<int> arr(0);
	EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, ConstMethods)
{
	int items[] = {1, 2, 3};
	const DynamicArray<int> arr(items, 3);

	EXPECT_EQ(arr.GetSize(), 3);
	EXPECT_EQ(arr.Get(0), 1);
}

TEST(DynamicArrayTest, DefaultConstructor)
{
	DynamicArray<int> arr;
	EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, SubscriptOperator)
{
	int items[] = {10, 20, 30};
	DynamicArray<int> arr(items, 3);

	EXPECT_EQ(arr[0], 10);
	EXPECT_EQ(arr[1], 20);

	arr[1] = 99;
	EXPECT_EQ(arr[1], 99);
}

TEST(DynamicArrayTest, SelfAssignment)
{
	int items[] = {1, 2, 3};
	DynamicArray<int> arr(items, 3);
	arr = arr;
	EXPECT_ARRAY(arr, 1, 2, 3);
}

TEST(DynamicArrayTest, CopyEmptyArray)
{
	DynamicArray<int> arr1(0);
	DynamicArray<int> arr2(arr1);
	EXPECT_EQ(arr2.GetSize(), 0);
}

TEST(DynamicArrayTest, ConstructorFromZeroSizeArray)
{
	int *items = nullptr;
	DynamicArray<int> arr(items, 0);
	EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, ConstSubscriptOperator)
{
	int items[] = {10, 20, 30};
	const DynamicArray<int> arr(items, 3);

	EXPECT_EQ(arr[0], 10);
	EXPECT_EQ(arr[1], 20);
	EXPECT_EQ(arr[2], 30);
}

TEST(DynamicArrayTest, SubscriptOperatorOutOfRange)
{
	DynamicArray<int> arr(3);
	EXPECT_ARRAY_THROW(arr[3], std::out_of_range);
}