//
// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/find.hpp"

//Тестирование при словах одинаковой длины
TEST(find, first)
{
	std::vector<int> vals = { 1, 2, 3, 4 };
	std::vector<std::pair<int, int>> tempVec;

	int res_s = search(vals, 1, tempVec);
	int res_bs = binSearch(vals, 1, tempVec);

	ASSERT_EQ(res_s, 0);
	ASSERT_EQ(res_bs, 0);
}

TEST(find, last)
{
	std::vector<int> vals = { 1, 2, 3, 4 };
	std::vector<std::pair<int, int>> tempVec;
	int find_val = 4;
	int res_s = search(vals, find_val, tempVec);
	int res_bs = binSearch(vals, find_val, tempVec);

	int res = 3;
	ASSERT_EQ(res_s, res);
	ASSERT_EQ(res_bs, res);

}

TEST(sort, negs)
{
	std::vector<int> vals = { -9999, -3, -2, -1, 1, 2, 3, 4, 10000 };
	std::vector<std::pair<int, int>> tempVec;
	int find_val = -1;
	int res_s = search(vals, find_val, tempVec);
	int res_bs = binSearch(vals, find_val, tempVec);

	int res = 3;
	ASSERT_EQ(res_s, res);
	ASSERT_EQ(res_bs, res);

}

TEST(sort, big_vals_near_start)
{
	std::vector<int> vals = { -9999, -3, -2, -1, 1, 2, 3, 4, 10000 };
	std::vector<std::pair<int, int>> tempVec;
	int find_val =  -3;
	int res_s = search(vals, find_val, tempVec);
	int res_bs = binSearch(vals, find_val, tempVec);

	int res = 1;
	ASSERT_EQ(res_s, res);
	ASSERT_EQ(res_bs, res);


}
