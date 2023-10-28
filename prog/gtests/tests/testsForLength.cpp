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
	std::vector<int> blockSort = vals;
	std::vector<int> shakerSort = vals;


	ASSERT_EQ(true, radix_sort == vals);
	ASSERT_EQ(true, blockSort == vals);
	ASSERT_EQ(true, shakerSort == vals);
}

