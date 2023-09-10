//
// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/table.hpp"

TEST(LenTest, EQLENTEST) {
	std::string st1 = "wwwwwwc";
	std::string st2 = "bbbbbbc";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 6;
	int LevLen  = 6;

	int lenMatDamerau =  mat.findMatrixDistDamerau(st1, st2);
	int lenRecurseMemDamerau = mat.findRecurseDistMemDamerau(st1, st2);
	int lenRecurseDamerau =  mat.findRecurseDistDamerau(st1, st2);

	int lenMatLev = mat.findMatrixDistLev(st1,st2);

	ASSERT_EQ(DamerauLen,lenMatDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseMemDamerau);
	ASSERT_EQ(LevLen,lenMatLev);
}


TEST(LenTest, DIFLENTEST) {
	std::string st1 = "AB";
	std::string st2 = "BA";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 1;
	int LevLen  = 2;

	int lenMatDamerau =  mat.findMatrixDistDamerau(st1, st2);
	int lenRecurseMemDamerau = mat.findRecurseDistMemDamerau(st1, st2);
	int lenRecurseDamerau =  mat.findRecurseDistDamerau(st1, st2);

	int lenMatLev = mat.findMatrixDistLev(st1,st2);

	ASSERT_EQ(DamerauLen,lenMatDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseMemDamerau);
	ASSERT_EQ(LevLen,lenMatLev);
}



TEST(LenTest, LongWords) {
	std::string st1 = "AKKAKKAKAKAAKBBABAK";
	std::string st2 = "AKAKVVKAKAKAKABABKA";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 7;
	int LevLen  = 6;

	int lenMatDamerau =  mat.findMatrixDistDamerau(st1, st2);
	int lenRecurseMemDamerau = mat.findRecurseDistMemDamerau(st1, st2);
	int lenRecurseDamerau =  mat.findRecurseDistDamerau(st1, st2);

	int lenMatLev = mat.findMatrixDistLev(st1,st2);

	ASSERT_EQ(DamerauLen,lenMatDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseMemDamerau);
	ASSERT_EQ(LevLen,lenMatLev);
}