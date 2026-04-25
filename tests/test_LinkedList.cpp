#include "../include/LinkedList.hpp"
#include <gtest/gtest.h>

TEST(LinkedListTest, DefaultConstructor)
{
	LinkedList<int> list;
	EXPECT_EQ(list.GetLength(), 0);
	EXPECT_THROW(list.GetFirst(), std::out_of_range);
	EXPECT_THROW(list.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, ConstructorFromArray)
{
	int items[] = {1, 2, 3, 4, 5};
	LinkedList<int> list(items, 5);
	EXPECT_EQ(list.GetLength(), 5);
	EXPECT_EQ(list.Get(0), 1);
	EXPECT_EQ(list.Get(1), 2);
	EXPECT_EQ(list.Get(2), 3);
	EXPECT_EQ(list.Get(3), 4);
	EXPECT_EQ(list.Get(4), 5);
}

TEST(LinkedListTest, ConstructorFromArrayWithNullptr)
{
	EXPECT_THROW(LinkedList<int> list(nullptr, 5), std::invalid_argument);
}

TEST(LinkedListTest, ConstructorFromArrayWithNegativeCount)
{
	int items[] = {1, 2, 3};
	EXPECT_THROW(LinkedList<int> list(items, -1), std::invalid_argument);
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

	EXPECT_EQ(list2.GetLength(), 3);
	EXPECT_EQ(list2.Get(0), 1);
	EXPECT_EQ(list2.Get(1), 2);
	EXPECT_EQ(list2.Get(2), 3);

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

	EXPECT_EQ(list2.GetLength(), 3);
	EXPECT_EQ(list2.Get(0), 1);
	EXPECT_EQ(list2.Get(1), 2);
	EXPECT_EQ(list2.Get(2), 3);
	EXPECT_THROW(list2.Get(3), std::out_of_range);
}

TEST(LinkedListTest, SelfAssignment)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	list = list;
	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 1);
	EXPECT_EQ(list.Get(1), 2);
	EXPECT_EQ(list.Get(2), 3);
}

TEST(LinkedListTest, MoveConstructor)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1(items, 3);
	LinkedList<int> list2(std::move(list1));

	EXPECT_EQ(list2.GetLength(), 3);
	EXPECT_EQ(list2.Get(0), 1);
	EXPECT_EQ(list2.Get(1), 2);
	EXPECT_EQ(list2.Get(2), 3);
	EXPECT_EQ(list1.GetLength(), 0);
}

TEST(LinkedListTest, MoveAssignmentOperator)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5};
	LinkedList<int> list1(items1, 3);
	LinkedList<int> list2(items2, 2);

	list2 = std::move(list1);

	EXPECT_EQ(list2.GetLength(), 3);
	EXPECT_EQ(list2.Get(0), 1);
	EXPECT_EQ(list2.Get(1), 2);
	EXPECT_EQ(list2.Get(2), 3);
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
	EXPECT_THROW(list.GetFirst(), std::out_of_range);
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
	EXPECT_THROW(list.GetLast(), std::out_of_range);
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
	EXPECT_THROW(list.Get(-1), std::out_of_range);
	EXPECT_THROW(list.Get(3), std::out_of_range);
	EXPECT_THROW(list.Get(100), std::out_of_range);
}

TEST(LinkedListTest, GetSubListValid)
{
	int items[] = {1, 2, 3, 4, 5};
	LinkedList<int> list(items, 5);
	LinkedList<int> sublist = list.GetSubList(1, 3);

	EXPECT_EQ(sublist.GetLength(), 3);
	EXPECT_EQ(sublist.Get(0), 2);
	EXPECT_EQ(sublist.Get(1), 3);
	EXPECT_EQ(sublist.Get(2), 4);
}

TEST(LinkedListTest, GetSubListSingleElement)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	LinkedList<int> sublist = list.GetSubList(1, 1);

	EXPECT_EQ(sublist.GetLength(), 1);
	EXPECT_EQ(sublist.Get(0), 2);
}

TEST(LinkedListTest, GetSubListStartIndexOutOfRange)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_THROW(list.GetSubList(-1, 2), std::out_of_range);
	EXPECT_THROW(list.GetSubList(3, 4), std::out_of_range);
}

TEST(LinkedListTest, GetSubListEndIndexOutOfRange)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_THROW(list.GetSubList(0, 3), std::out_of_range);
	EXPECT_THROW(list.GetSubList(0, 5), std::out_of_range);
}

TEST(LinkedListTest, GetSubListStartGreaterThanEnd)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_THROW(list.GetSubList(2, 1), std::invalid_argument);
}

TEST(LinkedListTest, Append)
{
	LinkedList<int> list;
	list.Append(10);
	list.Append(20);
	list.Append(30);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
	EXPECT_EQ(list.GetLast(), 30);
}

TEST(LinkedListTest, Prepend)
{
	LinkedList<int> list;
	list.Prepend(30);
	list.Prepend(20);
	list.Prepend(10);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
	EXPECT_EQ(list.GetFirst(), 10);
}

TEST(LinkedListTest, InsertAtBeginning)
{
	int items[] = {20, 30};
	LinkedList<int> list(items, 2);
	list.InsertAt(10, 0);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, InsertAtMiddle)
{
	int items[] = {10, 30};
	LinkedList<int> list(items, 2);
	list.InsertAt(20, 1);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, InsertAtEnd)
{
	int items[] = {10, 20};
	LinkedList<int> list(items, 2);
	list.InsertAt(30, 2);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 10);
	EXPECT_EQ(list.Get(1), 20);
	EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, InsertAtInvalidIndex)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	EXPECT_THROW(list.InsertAt(99, -1), std::out_of_range);
	EXPECT_THROW(list.InsertAt(99, 4), std::out_of_range);
}

TEST(LinkedListTest, Concat)
{
	int items1[] = {1, 2, 3};
	int items2[] = {4, 5, 6};
	LinkedList<int> list1(items1, 3);
	LinkedList<int> list2(items2, 3);
	LinkedList<int> result = list1.Concat(list2);

	EXPECT_EQ(result.GetLength(), 6);
	EXPECT_EQ(result.Get(0), 1);
	EXPECT_EQ(result.Get(1), 2);
	EXPECT_EQ(result.Get(2), 3);
	EXPECT_EQ(result.Get(3), 4);
	EXPECT_EQ(result.Get(4), 5);
	EXPECT_EQ(result.Get(5), 6);
}

TEST(LinkedListTest, ConcatWithEmpty)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1(items, 3);
	LinkedList<int> list2;
	LinkedList<int> result = list1.Concat(list2);

	EXPECT_EQ(result.GetLength(), 3);
	EXPECT_EQ(result.Get(0), 1);
	EXPECT_EQ(result.Get(1), 2);
	EXPECT_EQ(result.Get(2), 3);
}

TEST(LinkedListTest, ConcatEmptyWithNonEmpty)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list1;
	LinkedList<int> list2(items, 3);
	LinkedList<int> result = list1.Concat(list2);

	EXPECT_EQ(result.GetLength(), 3);
	EXPECT_EQ(result.Get(0), 1);
	EXPECT_EQ(result.Get(1), 2);
	EXPECT_EQ(result.Get(2), 3);
}

TEST(LinkedListTest, ConcatWithSelf)
{
	int items[] = {1, 2, 3};
	LinkedList<int> list(items, 3);
	LinkedList<int> result = list.Concat(list);

	EXPECT_EQ(result.GetLength(), 6);
	EXPECT_EQ(result.Get(0), 1);
	EXPECT_EQ(result.Get(1), 2);
	EXPECT_EQ(result.Get(2), 3);
	EXPECT_EQ(result.Get(3), 1);
	EXPECT_EQ(result.Get(4), 2);
	EXPECT_EQ(result.Get(5), 3);
}

TEST(LinkedListTest, ComplexOperations)
{
	LinkedList<int> list;
	list.Append(10);
	list.Prepend(5);
	list.InsertAt(7, 1);

	EXPECT_EQ(list.GetLength(), 3);
	EXPECT_EQ(list.Get(0), 5);
	EXPECT_EQ(list.Get(1), 7);
	EXPECT_EQ(list.Get(2), 10);

	LinkedList<int> sublist = list.GetSubList(0, 1);
	EXPECT_EQ(sublist.GetLength(), 2);
	EXPECT_EQ(sublist.Get(0), 5);
	EXPECT_EQ(sublist.Get(1), 7);
}