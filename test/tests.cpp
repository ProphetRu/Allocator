#include <gtest/gtest.h>

#include "CustomVector.hpp"
#include "CustomAllocator.hpp"

// Tests custom vector with default allocator
TEST(TestsCustomVectorWithDefaultAllocator, TestDefaultCtr) 
{
    // Arrange
	CustomVector<int> vec;

    // Act
	//

    // Assert
    ASSERT_EQ(vec.empty(), true);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestCtrWithParams) 
{
    // Arrange
	constexpr auto SIZE = 10u;
	constexpr auto VALUE = 42;

    // Act
	CustomVector<int> vec(SIZE, VALUE);

    // Assert
	ASSERT_EQ(vec.size(), SIZE);

	for (auto i = 0u; i < SIZE; ++i)
	{
		ASSERT_EQ(vec[i], VALUE);
	}
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodPushBack) 
{
    // Arrange
	CustomVector<int> vec;

    // Act
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(i);
	}

    // Assert
	ASSERT_EQ(vec.size(), 10u);
	for (unsigned i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(vec[i], static_cast<int>(i));
	}
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodSize) 
{
    // Arrange
	CustomVector<int> vec1(2, 42);
	CustomVector<int> vec2;

    // Act
	//

    // Assert
	ASSERT_EQ(vec1.size(), 2u);
	ASSERT_EQ(vec2.size(), 0u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodEmpty) 
{
    // Arrange
	CustomVector<int> vec1(2, 42);
	CustomVector<int> vec2;

    // Act
	//

    // Assert
	ASSERT_EQ(vec1.empty(), false);
	ASSERT_EQ(vec2.empty(), true);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodClear) 
{
    // Arrange
	CustomVector<int> vec(2, 42);

    // Act
	vec.clear();

    // Assert
	ASSERT_EQ(vec.empty(), true);
	ASSERT_EQ(vec.size(), 0u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodCapacity) 
{
    // Arrange
	CustomVector<int> vec{ };

    // Act
	ASSERT_EQ(vec.capacity(), 0u);

    // Assert
	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 1u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 2u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 4u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 4u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodPopBack) 
{
    // Arrange
	CustomVector<int> vec;

    // Act
	for (int i = 0; i < 3; ++i)
	{
		vec.push_back(i);
		vec.pop_back();
	}

    // Assert
	ASSERT_EQ(vec.empty(), true);
	ASSERT_EQ(vec.size(), 0u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodResize) 
{
    // Arrange
	CustomVector<int> vec;

    // Act
	vec.resize(10);

    // Assert
	ASSERT_EQ(vec.size(), 10u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestMethodReserve) 
{
    // Arrange
	CustomVector<int> vec;

    // Act
	vec.reserve(10);

    // Assert
	ASSERT_EQ(vec.capacity(), 10u);
}

TEST(TestsCustomVectorWithDefaultAllocator, TestOperatorAt) 
{
    // Arrange
	constexpr auto VALUE1 = 42;
	constexpr auto VALUE2 = 42;
	CustomVector<int> vec(2, VALUE1);

    // Act
	auto value = vec[0];
	ASSERT_EQ(value, VALUE1);

    // Assert
	vec[0] = VALUE2;
	value = vec[0];
	ASSERT_EQ(value, VALUE2);
}


// Tests custom vector with custom allocator
TEST(TestsCustomVectorWithCustomAllocator, TestDefaultCtr) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec;

    // Act
	//

    // Assert
    ASSERT_EQ(vec.empty(), true);
}

TEST(TestsCustomVectorWithCustomAllocator, TestCtrWithParams) 
{
    // Arrange
	constexpr auto SIZE = 10u;
	constexpr auto VALUE = 42;

    // Act
	CustomVector<int, CustomAllocator<int, 10>> vec(SIZE, VALUE);

    // Assert
	ASSERT_EQ(vec.size(), SIZE);

	for (auto i = 0u; i < SIZE; ++i)
	{
		ASSERT_EQ(vec[i], VALUE);
	}
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodPushBack) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 16>> vec;

    // Act
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(i);
	}

    // Assert
	ASSERT_EQ(vec.size(), 10u);
	for (unsigned i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(vec[i], static_cast<int>(i));
	}
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodPushBackException) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 2>> vec;

    // Act
	vec.push_back(1);
	vec.push_back(2);

    // Assert
	ASSERT_THROW(vec.push_back(3), std::bad_alloc);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodSize) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec1(2, 42);
	CustomVector<int, CustomAllocator<int, 10>> vec2;

    // Act
	//

    // Assert
	ASSERT_EQ(vec1.size(), 2u);
	ASSERT_EQ(vec2.size(), 0u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodEmpty) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec1(2, 42);
	CustomVector<int, CustomAllocator<int, 10>> vec2;

    // Act
	//

    // Assert
	ASSERT_EQ(vec1.empty(), false);
	ASSERT_EQ(vec2.empty(), true);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodClear) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec(2, 42);

    // Act
	vec.clear();

    // Assert
	ASSERT_EQ(vec.empty(), true);
	ASSERT_EQ(vec.size(), 0u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodCapacity) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec{ };

    // Act
	ASSERT_EQ(vec.capacity(), 0u);

    // Assert
	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 1u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 2u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 4u);

	vec.push_back(42);
	ASSERT_EQ(vec.capacity(), 4u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodPopBack) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec;

    // Act
	for (int i = 0; i < 3; ++i)
	{
		vec.push_back(i);
		vec.pop_back();
	}

    // Assert
	ASSERT_EQ(vec.empty(), true);
	ASSERT_EQ(vec.size(), 0u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodResize) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec;

    // Act
	vec.resize(10);

    // Assert
	ASSERT_EQ(vec.size(), 10u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestMethodReserve) 
{
    // Arrange
	CustomVector<int, CustomAllocator<int, 10>> vec;

    // Act
	vec.reserve(10);

    // Assert
	ASSERT_EQ(vec.capacity(), 10u);
}

TEST(TestsCustomVectorWithCustomAllocator, TestOperatorAt) 
{
    // Arrange
	constexpr auto VALUE1 = 42;
	constexpr auto VALUE2 = 42;
	CustomVector<int, CustomAllocator<int, 10>> vec(2, VALUE1);

    // Act
	auto value = vec[0];
	ASSERT_EQ(value, VALUE1);

    // Assert
	vec[0] = VALUE2;
	value = vec[0];
	ASSERT_EQ(value, VALUE2);
}


int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
