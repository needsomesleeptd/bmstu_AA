//
// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/sort.hpp"

//Тестирование при словах одинаковой длины
TEST(sort, already_sorted)
{
	std::vector<int> vals = { 1, 2, 3, 4 };

	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	radixSort(radix_sort);
	blockSort(block_sort, 2);
	shakerSort(shaker_sort);

	ASSERT_EQ(true, radix_sort == vals);
	ASSERT_EQ(true, block_sort == vals);
	ASSERT_EQ(true, shaker_sort == vals);
}

TEST(sort, reverse_sorted)
{
	std::vector<int> vals = { 4, 3, 2, 1 };

	std::vector<int> ref = { 1, 2, 3, 4 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	radixSort(radix_sort);
	blockSort(block_sort, 2);
	shakerSort(shaker_sort);

	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}

TEST(sort, not_sorted)
{
	std::vector<int> vals = { 3, 5, 1, 6 };

	std::vector<int> ref = { 1, 3, 5, 6 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	radixSort(radix_sort);
	blockSort(block_sort, 2);
	shakerSort(shaker_sort);

	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}

TEST(sort, one_value)
{
	std::vector<int> vals = { 1 };

	std::vector<int> ref = { 1 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	radixSort(radix_sort);
	blockSort(block_sort, 2);
	shakerSort(shaker_sort);

	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}

TEST(sort, negatives)
{
	std::vector<int> vals = { -5, -1, -3, -4, -2 };

	std::vector<int> ref = { -5, -4, -3, -2, -1 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	radixSort(radix_sort);
	blockSort(block_sort, 2);
	shakerSort(shaker_sort);

	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}

TEST(sort, positives_negatives)
{
	std::vector<int> vals = { 1, -3, 2, 9, -9, 4, 5, 0, 1 };

	std::vector<int> ref = { -9, -3, 0, 1, 1, 2, 4, 5, 9 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	blockSort(block_sort, 2);
	shakerSort(shaker_sort);
	radixSort(radix_sort);


	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}



TEST(sort, duplicates)
{
	std::vector<int> vals = { 1, -3, 2, 9, -9, 4, 5, 0, 1 };

	std::vector<int> ref = { -9, -3, 0, 1, 1, 2, 4, 5, 9 };
	std::vector<int> radix_sort = vals;
	std::vector<int> block_sort = vals;
	std::vector<int> shaker_sort = vals;

	blockSort(block_sort, 2);
	shakerSort(shaker_sort);
	radixSort(radix_sort);


	ASSERT_EQ(true, radix_sort == ref);
	ASSERT_EQ(true, block_sort == ref);
	ASSERT_EQ(true, shaker_sort == ref);

}