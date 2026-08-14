#include "Sequence.hpp"
#include "Vector.hpp"
#include <cmath>
#include <gtest/gtest.h>

#define EXPECT_VECTOR(arr, ...)                                                \
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

#define EXPECT_VECTOR_THROW(expression, exception_type)                        \
	EXPECT_THROW(expression, exception_type)

TEST(VectorTest, ConstructorDefault)
{
	Vector<int> vec1;
	EXPECT_EQ(vec1.GetSize(), 0);

	Vector<int> vec2{};
	EXPECT_EQ(vec2.GetSize(), 0);

	Vector<int> vec3 = Vector<int>();
	EXPECT_EQ(vec3.GetSize(), 0);
}

TEST(VectorTest, ConstructorWithSize)
{
	Vector<int> vec1(0);
	EXPECT_EQ(vec1.GetSize(), 0);

	Vector<int> vec2(1);
	EXPECT_EQ(vec2.GetSize(), 1);

	Vector<int> vec3(5);
	EXPECT_EQ(vec3.GetSize(), 5);

	Vector<int> vec4(999);
	EXPECT_EQ(vec4.GetSize(), 999);
}

TEST(VectorTest, ConstructorWithNegativeSize)
{
	EXPECT_VECTOR_THROW(Vector<int> vec(-1), std::invalid_argument);
}

TEST(VectorTest, ConstructorCopy)
{
	Vector<int> vec1(3);
	vec1.Set(0, 10);
	vec1.Set(1, 20);
	vec1.Set(2, 30);

	Vector<int> vec2(vec1);
	EXPECT_VECTOR(vec2, 10, 20, 30);

	vec2.Set(0, 100);
	EXPECT_EQ(vec1.Get(0), 10);
	EXPECT_EQ(vec2.Get(0), 100);
}

TEST(VectorTest, ConstructorMove)
{
	Vector<int> vec1(3);
	vec1.Set(0, 1);
	vec1.Set(1, 2);
	vec1.Set(2, 3);

	Vector<int> vec2(std::move(vec1));
	EXPECT_VECTOR(vec2, 1, 2, 3);
	EXPECT_EQ(vec1.GetSize(), 0);
}

TEST(VectorTest, AssignmentCopy)
{
	Vector<int> vec1(3);
	vec1.Set(0, 5);
	vec1.Set(1, 10);
	vec1.Set(2, 15);

	Vector<int> vec2(2);
	vec2 = vec1;

	EXPECT_VECTOR(vec2, 5, 10, 15);
	EXPECT_VECTOR(vec1, 5, 10, 15);

	vec2.Set(0, 100);
	EXPECT_EQ(vec1.Get(0), 5);
	EXPECT_EQ(vec2.Get(0), 100);
}

TEST(VectorTest, AssignmentCopySelf)
{
	Vector<int> vec(3);
	vec.Set(0, 1);
	vec.Set(1, 2);
	vec.Set(2, 3);

	vec = vec;
	EXPECT_VECTOR(vec, 1, 2, 3);
}

TEST(VectorTest, AssignmentMove)
{
	Vector<int> vec1(3);
	vec1.Set(0, 7);
	vec1.Set(1, 8);
	vec1.Set(2, 9);

	Vector<int> vec2(2);
	vec2 = std::move(vec1);

	EXPECT_VECTOR(vec2, 7, 8, 9);
	EXPECT_EQ(vec1.GetSize(), 0);
}

TEST(VectorTest, GetSet)
{
	Vector<int> vec(3);
	vec.Set(0, 100);
	vec.Set(1, 200);
	vec.Set(2, 300);

	EXPECT_EQ(vec.Get(0), 100);
	EXPECT_EQ(vec.Get(1), 200);
	EXPECT_EQ(vec.Get(2), 300);
}

TEST(VectorTest, GetOutOfRange)
{
	Vector<int> vec(3);
	EXPECT_VECTOR_THROW(vec.Get(-1), std::out_of_range);
	EXPECT_VECTOR_THROW(vec.Get(3), std::out_of_range);
	EXPECT_VECTOR_THROW(vec.Get(100), std::out_of_range);
}

TEST(VectorTest, SetOutOfRange)
{
	Vector<int> vec(3);
	EXPECT_VECTOR_THROW(vec.Set(-1, 10), std::out_of_range);
	EXPECT_VECTOR_THROW(vec.Set(3, 10), std::out_of_range);
	EXPECT_VECTOR_THROW(vec.Set(100, 10), std::out_of_range);
}

TEST(VectorTest, OperatorBracket)
{
	Vector<int> vec(3);
	vec[0] = 10;
	vec[1] = 20;
	vec[2] = 30;

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 20);
	EXPECT_EQ(vec[2], 30);

	const Vector<int> &constVec = vec;
	EXPECT_EQ(constVec[0], 10);
	EXPECT_EQ(constVec[1], 20);
	EXPECT_EQ(constVec[2], 30);
}

TEST(VectorTest, OperatorBracketOutOfRange)
{
	Vector<int> vec(3);
	EXPECT_VECTOR_THROW(vec[-1], std::out_of_range);
	EXPECT_VECTOR_THROW(vec[3], std::out_of_range);
}

TEST(VectorTest, OperatorPlus)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 4);
	v2.Set(1, 5);
	v2.Set(2, 6);

	Vector<int> result = v1 + v2;
	EXPECT_VECTOR(result, 5, 7, 9);
}

TEST(VectorTest, OperatorPlusDifferentSizes)
{
	Vector<int> v1(3);
	Vector<int> v2(2);
	EXPECT_VECTOR_THROW(v1 + v2, std::invalid_argument);
}

TEST(VectorTest, OperatorPlusEqual)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 4);
	v2.Set(1, 5);
	v2.Set(2, 6);

	v1 += v2;
	EXPECT_VECTOR(v1, 5, 7, 9);
}

TEST(VectorTest, OperatorMinus)
{
	Vector<int> v1(3);
	v1.Set(0, 5);
	v1.Set(1, 7);
	v1.Set(2, 9);

	Vector<int> v2(3);
	v2.Set(0, 1);
	v2.Set(1, 2);
	v2.Set(2, 3);

	Vector<int> result = v1 - v2;
	EXPECT_VECTOR(result, 4, 5, 6);
}

TEST(VectorTest, OperatorMinusDifferentSizes)
{
	Vector<int> v1(3);
	Vector<int> v2(2);
	EXPECT_VECTOR_THROW(v1 - v2, std::invalid_argument);
}

TEST(VectorTest, OperatorMinusEqual)
{
	Vector<int> v1(3);
	v1.Set(0, 5);
	v1.Set(1, 7);
	v1.Set(2, 9);

	Vector<int> v2(3);
	v2.Set(0, 1);
	v2.Set(1, 2);
	v2.Set(2, 3);

	v1 -= v2;
	EXPECT_VECTOR(v1, 4, 5, 6);
}

TEST(VectorTest, OperatorMultiplyScalar)
{
	Vector<int> v(3);
	v.Set(0, 1);
	v.Set(1, 2);
	v.Set(2, 3);

	Vector<int> result = v * 2;
	EXPECT_VECTOR(result, 2, 4, 6);

	Vector<int> result2 = v * 0;
	EXPECT_VECTOR(result2, 0, 0, 0);
}

TEST(VectorTest, OperatorMultiplyScalarEqual)
{
	Vector<int> v(3);
	v.Set(0, 1);
	v.Set(1, 2);
	v.Set(2, 3);

	v *= 2;
	EXPECT_VECTOR(v, 2, 4, 6);
}

TEST(VectorTest, OperatorEqual)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 1);
	v2.Set(1, 2);
	v2.Set(2, 3);

	Vector<int> v3(3);
	v3.Set(0, 1);
	v3.Set(1, 2);
	v3.Set(2, 4);

	Vector<int> v4(2);
	v4.Set(0, 1);
	v4.Set(1, 2);

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
}

TEST(VectorTest, OperatorNotEqual)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 1);
	v2.Set(1, 2);
	v2.Set(2, 3);

	Vector<int> v3(3);
	v3.Set(0, 1);
	v3.Set(1, 2);
	v3.Set(2, 4);

	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(VectorTest, Norm)
{
	Vector<int> v(3);
	v.Set(0, 3);
	v.Set(1, 4);
	v.Set(2, 0);

	EXPECT_DOUBLE_EQ(v.Norm(), 5.0);

	Vector<int> v2(2);
	v2.Set(0, 1);
	v2.Set(1, 1);
	EXPECT_DOUBLE_EQ(v2.Norm(), 1.4142);

	Vector<int> v3(0);
	EXPECT_DOUBLE_EQ(v3.Norm(), 0.0);
}

TEST(VectorTest, ScalarProduct)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 4);
	v2.Set(1, 5);
	v2.Set(2, 6);

	EXPECT_EQ(v1.ScalarProduct(v2), 1 * 4 + 2 * 5 + 3 * 6);
}

TEST(VectorTest, ScalarProductDifferentSizes)
{
	Vector<int> v1(3);
	Vector<int> v2(2);
	EXPECT_VECTOR_THROW(v1.ScalarProduct(v2), std::invalid_argument);
}

TEST(VectorTest, ToString)
{
	Vector<int> vec1(0);
	EXPECT_EQ(vec1.ToString(), "[]");

	Vector<int> vec2(3);
	vec2.Set(0, 1);
	vec2.Set(1, 2);
	vec2.Set(2, 3);
	EXPECT_EQ(vec2.ToString(), "[1, 2, 3]");

	Vector<int> vec3(1);
	vec3.Set(0, 42);
	EXPECT_EQ(vec3.ToString(), "[42]");
}

TEST(VectorTest, ComplexOperations)
{
	Vector<int> v1(3);
	v1.Set(0, 1);
	v1.Set(1, 2);
	v1.Set(2, 3);

	Vector<int> v2(3);
	v2.Set(0, 4);
	v2.Set(1, 5);
	v2.Set(2, 6);

	Vector<int> result = (v1 + v2) * 2 - v1;
	EXPECT_VECTOR(result, 9, 12, 15);

	Vector<int> v3(2);
	v3.Set(0, 3);
	v3.Set(1, 4);
	EXPECT_DOUBLE_EQ(v3.Norm(), 5.0);

	Vector<int> v4(2);
	v4.Set(0, 1);
	v4.Set(1, 2);
	EXPECT_EQ(v3.ScalarProduct(v4), 3 * 1 + 4 * 2);
}

TEST(VectorTest, MoveSemanticsPerformance)
{
	Vector<int> v1(1000);
	for (int i = 0; i < 1000; ++i) {
		v1.Set(i, i);
	}

	Vector<int> v2 = std::move(v1);
	EXPECT_EQ(v2.GetSize(), 1000);
	EXPECT_EQ(v1.GetSize(), 0);

	Vector<int> v3(500);
	v3 = std::move(v2);
	EXPECT_EQ(v3.GetSize(), 1000);
	EXPECT_EQ(v2.GetSize(), 0);
}