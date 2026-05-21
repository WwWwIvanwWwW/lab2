#include "LinkedList.hpp"
#include <gtest/gtest.h>

#define EXPECT_LIST(seq, ...)                                                  \
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

#define EXPECT_LIST_THROW(expression, exception_type)                          \
	EXPECT_THROW(expression, exception_type)

TEST(LinkedListTest, DefaultConstructor)
{
	LinkedList<int> list;
	EXPECT_EQ(list.GetLength(), 0);
	EXPECT_LIST_THROW(list.GetFirst(), std::out_of_range);
	EXPECT_LIST_THROW(list.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3, 4, 5};
	LinkedList<int> list(items, 5);
	EXPECT_LIST(list, 1, 2, 3, 4, 5);
}

TEST(LinkedListTest, ConstructorFromArrayWithNullptr)
{
	EXPECT_LIST_THROW(LinkedList<int> list(nullptr, 5), std::invalid_argument);
}

TEST(LinkedListTest, ConstructorFromArrayWithNegativeCount)
{
	int items[] = {1, 2, 3};
	EXPECT_LIST_THROW(LinkedList<int> list(items, -1), std::invalid_argument);
}

TEST(LinkedListTest, ConstructorFromArrayWithNullptrAndZeroCount)
{
	LinkedList<int> list(nullptr, 0);
	EXPECT_EQ(list.GetLength(), 0);
}

TEST(LinkedListTest, CopyConstructor)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1(items, 3);
	LinkedList<int> list2(list1);

	EXPECT_LIST(list2, 1, 2, 3);

	list1.Append(100);
	EXPECT_EQ(list2.GetLength(), 3);
}

TEST(LinkedListTest, CopyAssignmentOperator)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6, 7};
	LinkedList<int> list1(items1, 3);
	LinkedList<int> list2(items2, 4);

	list2 = list1;

	EXPECT_LIST(list2, 1, 2, 3);
	EXPECT_LIST_THROW(list2.Get(3), std::out_of_range);
}

TEST(LinkedListTest, SelfAssignment)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	list = list;
	EXPECT_LIST(list, 1, 2, 3);
}

TEST(LinkedListTest, MoveConstructor)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1(items, 3);
	LinkedList<int> list2(std::move(list1));

	EXPECT_LIST(list2, 1, 2, 3);
	EXPECT_EQ(list1.GetLength(), 0);
}

TEST(LinkedListTest, MoveAssignmentOperator)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5};
	LinkedList<int> list1(items1, 3);
	LinkedList<int> list2(items2, 2);

	list2 = std::move(list1);

	EXPECT_LIST(list2, 1, 2, 3);
	EXPECT_EQ(list1.GetLength(), 0);
}

TEST(LinkedListTest, GetFirst)
{
	int items[] = {10, 20, 30};
	LinkedList<int> list(items, 3);
	EXPECT_EQ(list.GetFirst(), 10);
}

TEST(LinkedListTest, GetFirstOnEmptyList)
{
	LinkedList<int> list;
	EXPECT_LIST_THROW(list.GetFirst(), std::out_of_range);
}

TEST(LinkedListTest, GetLast)
{
	int items[] = {10, 20, 30};
	LinkedList<int> list(items, 3);
	EXPECT_EQ(list.GetLast(), 30);
}

TEST(LinkedListTest, GetLastOnEmptyList)
{
	LinkedList<int> list;
	EXPECT_LIST_THROW(list.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, GetValidIndex)
{
	int items[] = {10, 20, 30};
	LinkedList<int> list(items, 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, GetInvalidIndex)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_LIST_THROW(list.Get(-1), std::out_of_range);
	EXPECT_LIST_THROW(list.Get(3), std::out_of_range);
	EXPECT_LIST_THROW(list.Get(100), std::out_of_range);
}

TEST(LinkedListTest, GetSubListValid)
{
	int items[] = {1, 2, 3, 4, 5};
	LinkedList<int> list(items, 5);
	LinkedList<int> sublist = list.GetSubList(1, 3);
	EXPECT_LIST(sublist, 2, 3, 4);
}

TEST(LinkedListTest, GetSubListSingleElement)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	LinkedList<int> sublist = list.GetSubList(1, 1);
	EXPECT_LIST(sublist, 2);
}

TEST(LinkedListTest, GetSubListStartIndexOutOfRange)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_LIST_THROW(list.GetSubList(-1, 2), std::out_of_range);
	EXPECT_LIST_THROW(list.GetSubList(3, 4), std::out_of_range);
}

TEST(LinkedListTest, GetSubListEndIndexOutOfRange)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_LIST_THROW(list.GetSubList(0, 3), std::out_of_range);
	EXPECT_LIST_THROW(list.GetSubList(0, 5), std::out_of_range);
}

TEST(LinkedListTest, GetSubListStartGreaterThanEnd)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_LIST_THROW(list.GetSubList(2, 1), std::invalid_argument);
}

TEST(LinkedListTest, Append)
{
	LinkedList<int> list;
	list.Append(10);
	list.Append(20);
	list.Append(30);
	EXPECT_LIST(list, 10, 20, 30);
	EXPECT_EQ(list.GetLast(), 30);
}

TEST(LinkedListTest, Prepend)
{
	LinkedList<int> list;
	list.Prepend(30);
	list.Prepend(20);
	list.Prepend(10);
	EXPECT_LIST(list, 10, 20, 30);
	EXPECT_EQ(list.GetFirst(), 10);
}

TEST(LinkedListTest, InsertAtBeginning)
{
	int items[] = {20, 30};
	LinkedList<int> list(items, 2);
	list.InsertAt(10, 0);
	EXPECT_LIST(list, 10, 20, 30);
}

TEST(LinkedListTest, InsertAtMiddle)
{
	int items[] = {10, 30};
	LinkedList<int> list(items, 2);
	list.InsertAt(20, 1);
	EXPECT_LIST(list, 10, 20, 30);
}

TEST(LinkedListTest, InsertAtEnd)
{
	int items[] = {10, 20};
	LinkedList<int> list(items, 2);
	list.InsertAt(30, 2);
	EXPECT_LIST(list, 10, 20, 30);
}

TEST(LinkedListTest, InsertAtInvalidIndex)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_LIST_THROW(list.InsertAt(99, -1), std::out_of_range);
	EXPECT_LIST_THROW(list.InsertAt(99, 4), std::out_of_range);
}

TEST(LinkedListTest, Concat)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6};
	LinkedList<int> list1(items1, 3);
	LinkedList<int> list2(items2, 3);
	LinkedList<int> result = list1.Concat(list2);
	EXPECT_LIST(result, 1, 2, 3, 4, 5, 6);
}

TEST(LinkedListTest, ConcatWithEmpty)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1(items, 3);
	LinkedList<int> list2;
	LinkedList<int> result = list1.Concat(list2);
	EXPECT_LIST(result, 1, 2, 3);
}

TEST(LinkedListTest, ConcatEmptyWithNonEmpty)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1;
	LinkedList<int> list2(items, 3);
	LinkedList<int> result = list1.Concat(list2);
	EXPECT_LIST(result, 1, 2, 3);
}

TEST(LinkedListTest, ConcatWithSelf)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	LinkedList<int> result = list.Concat(list);
	EXPECT_LIST(result, 1, 2, 3, 1, 2, 3);
}

TEST(LinkedListTest, ComplexOperations)
{
	LinkedList<int> list;
	list.Append(10);
	list.Prepend(5);
	list.InsertAt(7, 1);

	EXPECT_LIST(list, 5, 7, 10);

	LinkedList<int> sublist = list.GetSubList(0, 1);
	EXPECT_LIST(sublist, 5, 7);
}