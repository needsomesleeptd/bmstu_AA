//
// Created by Андрей on 10/09/2023.
//
#include <gtest/gtest.h>
#include "../../src/table.hpp"

bool isMatrixiesEqual(Matrix& mat1, Matrix& mat2)
{
	if (mat1._n != mat2._n || mat1._m != mat2._m)
		return false;

	for (size_t i = 0; i < mat1._n; i++)
	{
		for (size_t j = 0; j < mat1._m; j++)
			if (mat1._table[i][j] != mat2._table[i][j])
				return false;
	}
	return true;
}

//Тестирование при словах одинаковой длины
TEST(MatTest, OnesMatrixTest)
{
	int n = 3;
	int m = 3;
	int k = 3;
	Matrix mat1(n, m);
	Matrix mat2(m, k);

	mat1._table = {{ 1, 2, 3 },
	               { 2, 3, 4 },
	               { 4, 6, 7 }
	};
	mat2._table = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};
	Matrix ref_mat(n, k);
	ref_mat._table = {{ 1, 2, 3 },
	                  { 2, 3, 4 },
	                  { 4, 6, 7 }
	};
	Matrix res_std = mat1.dot(mat2);
	Matrix res_vin = mat1.dot_vin(mat2);
	Matrix res_vin_opt = mat1.dot_vin_opt(mat2);

	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_std), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin_opt), true);

}

//Тестирование с различными результатами при использовании различных расстояний
TEST(MatTest, EQDimTest)
{
	int n = 3;
	int m = 3;
	int k = 3;
	Matrix mat1(n, m);
	Matrix mat2(m, k);

	mat1._table = {{ 1, 2, 3 },
	               { 2, 3, 4 },
	               { 4, 6, 7 }
	};
	mat2._table = {
		{ 1, 2, 3 },
		{ 0, 1, 4 },
		{ 5, 0, 1 }
	};
	Matrix ref_mat(n, k);
	ref_mat._table = {{ 16, 4, 14 },
	                  { 22, 7, 22 },
	                  { 39, 14, 43 }
	};
	Matrix res_std = mat1.dot(mat2);
	Matrix res_vin = mat1.dot_vin(mat2);
	Matrix res_vin_opt = mat1.dot_vin_opt(mat2);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_std), true);

	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin_opt), true);

}


//Различающийся результат расстояний при словах различной длины
TEST(MatTest, diffDims)
{
	int n = 4;
	int m = 3;
	int k = 6;
	Matrix mat1(n, m);
	Matrix mat2(m, k);

	mat1._table = {{ 1, 2, 3 },
	               { 2, 3, 4 },
	               { 4, 6, 7 },
	               { 1, 4, -2 }

	};
	mat2._table = {
		{ 1, 2, 3, 0, 7, 8 },
		{ 0, 1, 4, 0, 5, 6 },
		{ 5, 0, 1, 0, 3, 4 }
	};
	Matrix ref_mat(n, k);
	ref_mat._table = {{ 16, 4, 14, 0, 26, 32 },
	                  { 22, 7, 22, 0, 41, 50 },
	                  { 39, 14, 43, 0, 79, 96 },
	                  { -9, 6, 17, 0, 21, 24 }
	};
	Matrix res_std = mat1.dot(mat2);
	Matrix res_vin = mat1.dot_vin(mat2);
	Matrix res_vin_opt = mat1.dot_vin_opt(mat2);

	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_std), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin_opt), true);
}

//Тестирование подобное тесту на русском языке
TEST(MatTest, n_odd_dims)
{
	int n = 2;
	int m = 2;
	int k = 2;
	Matrix mat1(n, m);
	Matrix mat2(m, k);

	mat1._table = {{ 1, 2 },
	               { 3, 4 }
	};

	mat2._table = {{ 1, 0 },
	               { 0, 1 }
	};
	Matrix ref_mat(n, k);
	ref_mat._table = {{ 1, 2 },
	                  { 3, 4 }
	};
	Matrix res_std = mat1.dot(mat2);
	Matrix res_vin = mat1.dot_vin(mat2);
	Matrix res_vin_opt = mat1.dot_vin_opt(mat2);

	Matrix res_shtr = mat1.dot_shtrassen(mat2);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_std), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_shtr), true);
	ASSERT_EQ(isMatrixiesEqual(ref_mat, res_vin_opt), true);
};

