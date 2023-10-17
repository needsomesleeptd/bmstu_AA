//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "table.hpp"
#include "cassert"

Matrix::Matrix(int n, int m)
{
	_table = std::vector<std::vector<int>>(n, std::vector<int>(m));
	_n = n;
	_m = m;

}

void Matrix::printMatrix()
{
	for (size_t i = 0; i < _n; i++)
	{
		for (size_t j = 0; j < _m; j++)
		{
			std::wcout << _table[i][j] << L" ";
		}
		std::wcout << std::endl;
	}
}
Matrix Matrix::dot(const Matrix& other)
{
	Matrix mat_res = Matrix(this->_n, other._m);
	for (size_t i = 0; i < this->_n; i++)
	{
		for (size_t j = 0; j < other._m; j++)
		{
			mat_res._table[i][j] = 0;
			for (size_t k = 0; k < other._n; k++)
				mat_res._table[i][j] = mat_res._table[i][j] + this->_table[i][k] * other._table[k][j];
		}
	}
	return mat_res;
}
Matrix Matrix::dot_vin(const Matrix& other)
{
	//size_t d = other._n / 2;
	Matrix mat_res = Matrix(this->_n, other._m);
	std::vector<int> rowFactor(this->_n);
	std::vector<int> columnFactor(other._m);
	for (size_t i = 0; i < rowFactor.size(); i++)
	{
		for (size_t j = 0; j < this->_m / 2; j++)
			rowFactor[i] = rowFactor[i] + this->_table[i][2 * j + 1] * this->_table[i][2 * j];
	}

	for (size_t i = 0; i < columnFactor.size(); i++)
	{
		for (size_t j = 0; j < other._n / 2; j++)
			columnFactor[i] = columnFactor[i] + other._table[2 * j + 1][i] * other._table[2 * j][i];
	}

	for (size_t i = 0; i < this->_n; i++)
		for (size_t j = 0; j < other._m; j++)
		{
			mat_res._table[i][j] = -rowFactor[i] - columnFactor[i];
			for (size_t k = 0; k < this->_m / 2; k++)
			{
				mat_res._table[i][j] = mat_res._table[i][j] + (this->_table[i][2 * k + 1] + other._table[2 * k][j])
					* (this->_table[i][2 * k] + other._table[2 * k + 1][j]);

			}
		}

	if (this->_m % 2 != 0)
		for (size_t i = 0; i < this->_n; i++)
			for (size_t j = 0; j < other._m; j++)
				mat_res._table[i][j] =
					mat_res._table[i][j] + this->_table[i][this->_m - 1] * other._table[other._n - 1][j];

	return mat_res;
}
Matrix Matrix::dot_vin_opt(const Matrix& other)
{
	size_t d = other._n / 2;
	Matrix mat_res = Matrix(this->_n, other._m);
	std::vector<int> rowFactor(this->_n);
	std::vector<int> columnFactor(other._m);
	for (size_t i = 0; i < rowFactor.size(); i++)
	{
		rowFactor[i] = this->_table[i][0] * this->_table[i][1];
		for (size_t j = 1; j < d; j++)
			rowFactor[i] = rowFactor[i] + this->_table[i][2 * j + 1] * this->_table[i][2 * j];
	}

	for (size_t i = 0; i < columnFactor.size(); i++)
	{
		columnFactor[i] = other._table[0][i] * other._table[1][i];
		for (size_t j = 1; j < d; j++)
			columnFactor[i] = columnFactor[i] + other._table[2 * j + 1][i] * other._table[2 * j][i];
	}

	for (size_t i = 0; i < this->_n; i++)
		for (size_t j = 0; j < this->_m; j++)
		{
			mat_res._table[i][j] = -rowFactor[i] - columnFactor[i];
			for (size_t k = 0; k < d; k++)
			{
				mat_res._table[i][j] = mat_res._table[i][j] + (this->_table[i][2 * k + 1] + other._table[2 * k][j])
					* (this->_table[i][2 * k] + other._table[2 * k + 1][j]);

			}
		}

	if (this->_n % 2 != 0)
		for (size_t i = 0; i < this->_n; i++)
			for (size_t j = 0; j < other._m; j++)
				mat_res._table[i][j] =
					mat_res._table[i][j] + this->_table[i][this->_m - 1] * other._table[other._n - 1][j];

	return mat_res;
}

std::vector<int> operator+(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
	std::vector<int> result;
	size_t size = std::min(vec1.size(), vec2.size());

	for (size_t i = 0; i < size; i++)
	{
		result.push_back(vec1[i] + vec2[i]);
	}

	return result;
}

std::vector<std::vector<int>> operator+(const std::vector<std::vector<int>>& mat1,
	const std::vector<std::vector<int>>& mat2)
{
	size_t n = mat1.size();
	std::vector<std::vector<int>> result(n, std::vector<int>(n));;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
			result[i][j] = mat1[i][j] + mat2[i][j];
	}

	return result;
}
std::vector<std::vector<int>> operator-(const std::vector<std::vector<int>>& mat1,
	const std::vector<std::vector<int>>& mat2)
{
	size_t n = mat1.size();
	std::vector<std::vector<int>> result(n, std::vector<int>(n));;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
			result[i][j] = mat1[i][j] - mat2[i][j];
	}

	return result;
}

std::vector<std::vector<int>> strassenMultiply(const std::vector<std::vector<int>>& matrix1,
	const std::vector<std::vector<int>>& matrix2)
{
	size_t n = matrix1.size();

	// Базовый случай для матриц размером 1x1
	if (n == 1) {
		std::vector<std::vector<int>> result(1, std::vector<int>(1, 0));
		result[0][0] = matrix1[0][0] * matrix2[0][0];
		return result;
	}

	// Деление матриц на подматрицы
	size_t half = n / 2;
	std::vector<std::vector<int>> a11(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> a12(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> a21(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> a22(half, std::vector<int>(half, 0));

	std::vector<std::vector<int>> b11(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> b12(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> b21(half, std::vector<int>(half, 0));
	std::vector<std::vector<int>> b22(half, std::vector<int>(half, 0));

	for (size_t i = 0; i < half; i++) {
		for (size_t j = 0; j < half; j++) {
			a11[i][j] = matrix1[i][j];
			a12[i][j] = matrix1[i][j + half];
			a21[i][j] = matrix1[i + half][j];
			a22[i][j] = matrix1[i + half][j + half];

			b11[i][j] = matrix2[i][j];
			b12[i][j] = matrix2[i][j + half];
			b21[i][j] = matrix2[i + half][j];
			b22[i][j] = matrix2[i + half][j + half];
		}
	}

	// Вычисление рекурсивных произведений
	std::vector<std::vector<int>> m1 = strassenMultiply(a11, b12 - b22);
	std::vector<std::vector<int>> m2 = strassenMultiply(a11 + a12, b22);
	std::vector<std::vector<int>> m3 = strassenMultiply(a21 + a22, b11);
	std::vector<std::vector<int>> m4 = strassenMultiply(a22, b21 - b11);
	std::vector<std::vector<int>> m5 = strassenMultiply(a11 + a22, b11 + b22);
	std::vector<std::vector<int>> m6 = strassenMultiply(a12 - a22, b21 + b22);
	std::vector<std::vector<int>> m7 = strassenMultiply(a11 - a21, b11 + b12);

	// Вычисление подматриц результата
	std::vector<std::vector<int>> c11 = m5 + m4 - m2 + m6;
	std::vector<std::vector<int>> c12 = m1 + m2;
	std::vector<std::vector<int>> c21 = m3 + m4;
	std::vector<std::vector<int>> c22 = m5 + m1 - m3 - m7;

	// Составление результирующей матрицы
	std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
	for (size_t i = 0; i < half; i++) {
		for (size_t j = 0; j < half; j++) {
			result[i][j] = c11[i][j];
			result[i][j + half] = c12[i][j];
			result[i + half][j] = c21[i][j];
			result[i + half][j + half] = c22[i][j];
		}
	}

	return result;
}

Matrix Matrix::dot_shtrassen(const Matrix& other)
{
	std::vector<std::vector<int>> vals = strassenMultiply(this->_table, other._table);
	Matrix mat(vals.size(),vals[0].size());
	mat._table = vals;
	return mat;
}


