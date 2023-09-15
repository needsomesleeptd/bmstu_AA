//
// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/table.hpp"

//Тестирование при словах одинаковой длины
TEST(LenTest, EQLENTEST) {
	std::wstring st1 = L"wwwwwwc";
	std::wstring st2 = L"bbbbbbc";
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

//Тестирование с различными результатами при использовании различных расстояний
TEST(LenTest, DIFLENTEST) {
	std::wstring st1 = L"AB";
	std::wstring st2 = L"BA";
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


//Различающийся результат расстояний при словах различной длины
TEST(LenTest, LongWords) {
	std::wstring st1 = L"KAKAKAKABABKA";
	std::wstring st2 = L"AKAAKBBABAK";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 4;
	int LevLen  = 5;

	int lenMatDamerau =  mat.findMatrixDistDamerau(st1, st2);
	int lenRecurseMemDamerau = mat.findRecurseDistMemDamerau(st1, st2);
	int lenRecurseDamerau =  mat.findRecurseDistDamerau(st1, st2);

	int lenMatLev = mat.findMatrixDistLev(st1,st2);

	ASSERT_EQ(DamerauLen,lenMatDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseMemDamerau);
	ASSERT_EQ(LevLen,lenMatLev);
}

//Тестирование подобное тесту на русском языке
TEST(LenTest, English) {
	std::wstring st1 = L"BCA";
	std::wstring st2 = L"ABC";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 2;
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

//Использование русских букв
TEST(LenTest, Russian) {
	std::wstring st1 = L"ВФА";
	std::wstring st2 = L"АВФ";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 2;
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

//Большая разница в длине слов
TEST(LenTest, BIGSIZEDIFF) {
	std::wstring st1 = L"ADFS";
	std::wstring st2 = L"ABFDSABDDASDADADF";
	Matrix mat(st1.size(),st2.size());

	int DamerauLen = 14;
	int LevLen  = 14;

	int lenMatDamerau =  mat.findMatrixDistDamerau(st1, st2);
	int lenRecurseMemDamerau = mat.findRecurseDistMemDamerau(st1, st2);
	int lenRecurseDamerau =  mat.findRecurseDistDamerau(st1, st2);

	int lenMatLev = mat.findMatrixDistLev(st1,st2);

	ASSERT_EQ(DamerauLen,lenMatDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseDamerau);
	ASSERT_EQ(DamerauLen,lenRecurseMemDamerau);
	ASSERT_EQ(LevLen,lenMatLev);
}