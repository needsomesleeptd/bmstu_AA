// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/sorts.h"

//Тестирование при словах одинаковой длины
TEST(sort, already_sorted)
{
	std::vector<int> vals = { 1, 2, 3, 4 };

	std::vector<int> merge_sort = vals;
	std::vector<int> merge_sort_multithread = vals;

	mergeSort(merge_sort,0,merge_sort.size() - 1);
	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);

	ASSERT_EQ(true, merge_sort == vals);
	ASSERT_EQ(true, merge_sort_multithread == vals);
}

TEST(sort, reverse_sorted)
{
	std::vector<int> vals = { 4, 3, 2, 1 };

	std::vector<int> ref = { 1, 2, 3, 4 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSort(merge_sort,0,merge_sort.size() - 1);;
	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, not_sorted)
{
	std::vector<int> vals = { 3, 5, 1, 6 };

	std::vector<int> ref = { 1, 3, 5, 6 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSort(merge_sort,0,merge_sort.size() - 1);;
	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, one_value)
{
	std::vector<int> vals = { 1 };

	std::vector<int> ref = { 1 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSort(merge_sort,0,merge_sort.size() - 1);;
	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, negatives)
{
	std::vector<int> vals = { -5, -1, -3, -4, -2 };

	std::vector<int> ref = { -5, -4, -3, -2, -1 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSort(merge_sort,0,merge_sort.size() - 1);;
	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, positives_negatives)
{
	std::vector<int> vals = { 1, -3, 2, 9, -9, 4, 5, 0, 1 };

	std::vector<int> ref = { -9, -3, 0, 1, 1, 2, 4, 5, 9 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	
	mergeSort(merge_sort,0,merge_sort.size() - 1);;

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, duplicates)
{
	std::vector<int> vals = { 1, -3, 2, 9, -9, 4, 5, 0, 1 };

	std::vector<int> ref = { -9, -3, 0, 1, 1, 2, 4, 5, 9 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);
	
	mergeSort(merge_sort,0,merge_sort.size() - 1);;

	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}

TEST(sort, big_numbers)
{
	std::vector<int> vals = { -1231, 444411, -12, 13, 24, 437, 8, 9, 3211, -10,0 };

	std::vector<int> ref = { -1231, -12, -10,0, 8, 9, 13, 24, 437, 3211, 444411 };
	std::vector<int> merge_sort = vals;
	
	std::vector<int> merge_sort_multithread = vals;

	mergeSortMultiThread(merge_sort_multithread,0,merge_sort_multithread.size() - 1, 2);


	mergeSort(merge_sort,0,merge_sort.size() - 1);;


	ASSERT_EQ(true, merge_sort == ref);
	
	ASSERT_EQ(true, merge_sort_multithread == ref);

}