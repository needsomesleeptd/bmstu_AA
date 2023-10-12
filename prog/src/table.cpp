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
	size_t d = other._n / 2;
	Matrix mat_res = Matrix(this->_n, other._m);
	std::vector<int> rowFactor(this->_n);
	std::vector<int> columnFactor(other._m);
	for (size_t i = 0; i < rowFactor.size(); i++)
	{
		rowFactor[i] = this->_table[i][1] * this->_table[i][2];
		for (size_t j = 0; j < d; j++)
			rowFactor[i] = rowFactor[i] + this->_table[i][2 * j - 1] * this->_table[i][2 * j];
	}

	for (size_t i = 0; i < columnFactor.size(); i++)
	{
		columnFactor[i] = other._table[1][i] * other._table[2][i];
		for (size_t j = 1; j < d; j++)
			columnFactor[i] = columnFactor[i] + other._table[2 * j - 1][i] * other._table[2 * j][i];
	}

	for (size_t i = 0; i < this->_n; i++)
		for (size_t j = 0; j < this->_m; j++)
		{
			mat_res._table[i][j] = -rowFactor[i] - columnFactor[i];
			for (size_t k = 1; k < d; k++)
			{
				mat_res._table[i][j] = mat_res._table[i][j] + (this->_table[i][2 * k - 1] + other._table[2 * k][j])
					* (this->_table[i][2 * k] + other._table[2 * k - 1][j]);

			}
		}

	if (this->_n % 2 != 0)
		for (size_t i = 0; i < this->_n; i++)
			for (size_t j = 0; j < other._m; j++)
				mat_res._table[i][j] = mat_res._table[i][j] + this->_table[i][this->_m - 1] * other._table[other._n - 1][j];

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
		rowFactor[i] = this->_table[i][1] * this->_table[i][2];
		for (size_t j = 0; j < d; j++)
			rowFactor[i] += this->_table[i][(1 << j) - 1] * this->_table[i][1 << j];
	}

	for (size_t i = 0; i < columnFactor.size(); i++)
	{
		columnFactor[i] = other._table[1][i] * other._table[2][i];
		for (size_t j = 2; j < d; j++)
			columnFactor[i] += other._table[(1 << j) - 1][i] * other._table[1 << j][i];
	}

	for (size_t i = 0; i < this->_n; i++)
		for (size_t j = 0; j < this->_m; j++)
		{
			mat_res._table[i][j] = -rowFactor[i] - columnFactor[i];
			for (size_t k = 0; k < d; k++)
			{
				mat_res._table[i][j] += (this->_table[i][(1 << k) - 1] + other._table[2 * k][j])
					* (this->_table[i][2 * k] + other._table[(1 << k) - 1][j]);

			}
		}

	if (this->_n % 2 != 0)
		for (size_t i = 0; i < this->_n; i++)
			for (size_t j = 0; j < other._m; j++)
				mat_res._table[i][j] += this->_table[i][this->_m - 1] * other._table[other._n - 1][j];

	return mat_res;
}



