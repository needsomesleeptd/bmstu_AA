//
// Created by Андрей on 10/09/2023.
//
#include "gtest/gtest.h"


#include <locale>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}