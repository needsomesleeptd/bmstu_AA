//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "table.hpp"
#include "cassert"

Matrix::Matrix(int n, int m)
{
	_table = std::vector<std::vector<int>>(n + 1, std::vector<int>(m + 1));
	_n = n + 1;
	_m = m + 1;

}
size_t Matrix::findMatrixDistDamerau(const std::wstring& st1, const std::wstring& st2)
{
	int n = st1.size() + 1;
	int m = st2.size() + 1;
	if (n > _n || m > _m)
		assert(0);
	_table[0][0] = 0;
	for (int i = 1; i < n; i++)
		_table[i][0] = i;
	for (int j = 1; j < m; j++)
		_table[0][j] = j;
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{

			_table[i][j] = std::min(_table[i][j - 1] + 1, _table[i - 1][j] + 1);
			int extraStep = 0;
			if (st1[i - 1] != st2[j - 1])
				extraStep++;

			_table[i][j] = std::min(_table[i][j], _table[i - 1][j - 1] + extraStep);
			if (i > 1 && j > 1)
			{
				if (st1[i - 1] == st2[j - 2] && st1[i - 2] == st2[j - 1])
					_table[i][j] = std::min(_table[i][j], _table[i - 2][j - 2] + 1);
			}
		}
	}
	return _table[n - 1][m - 1];
}

size_t Matrix::findMatrixDistLev(const std::wstring& st1, const std::wstring& st2)
{
	int n = st1.size() + 1;
	int m = st2.size() + 1;
	if (n > _n || m > _m)
		assert(0);
	_table[0][0] = 0;
	for (int i = 1; i < n; i++)
		_table[i][0] = i;
	for (int j = 1; j < m; j++)
		_table[0][j] = j;
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{

			_table[i][j] = std::min(_table[i][j - 1] + 1, _table[i - 1][j] + 1);
			int extraStep = 0;
			if (st1[i - 1] != st2[j - 1])
				extraStep++;
			_table[i][j] = std::min(_table[i][j], _table[i - 1][j - 1] + extraStep);
		}
	}
	return _table[n - 1][m - 1];
}

void Matrix::printMatrix()
{
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _m; j++)
		{
			std::wcout << _table[i][j] << L" ";
		}
		std::wcout << std::endl;
	}
}

size_t RecurseDistDamerau(const std::wstring& st1, const std::wstring& st2, int size1, int size2)
{
	if (size1 == 0)
		return size2;
	if (size2 == 0)
		return size1;

	size_t extraStep = 0;
	if (st1[size1 - 1] != st2[size2 - 1])
		extraStep++;

	size_t cutLeft = RecurseDistDamerau(st1, st2, size1 - 1, size2) + 1;
	size_t cutRight = RecurseDistDamerau(st1, st2, size1, size2 - 1) + 1;
	size_t cutBoth = RecurseDistDamerau(st1, st2, size1 - 1, size2 - 1) + extraStep;
	size_t DamerauCut = cutBoth + 1;
	if (size1 > 1 && size2 > 1 && st1[size1 - 1] == st2[size2 - 2]
		&& st1[size1 - 2] == st2[size2 - 1])
		DamerauCut = RecurseDistDamerau(st1, st2, size1 - 2, size2 - 2) + 1;

	cutBoth = std::min(DamerauCut, cutBoth); //need static here
	size_t chosenOne = std::min(std::min(cutRight, cutLeft), cutBoth);
	return chosenOne;
}

size_t RecurseDistMemDamerau(const std::wstring& st1,
	const std::wstring& st2,
	int lastIndex1,
	int lastIndex2,
	Matrix& mat)
{
	//std::cout<< "i " << "j " << lastIndex1 << " " << lastIndex2 << std::endl;
	if (mat._table[lastIndex1][lastIndex2] != INF)
		return mat._table[lastIndex1][lastIndex2];

	if (lastIndex1 == 0)
	{
		mat._table[lastIndex1][lastIndex2] = lastIndex2;
		return lastIndex2;
	}
	if (lastIndex2 == 0)
	{
		mat._table[lastIndex1][lastIndex2] = lastIndex1;
		return lastIndex1;
	}



	int extraStep = 0;
	if (st1[lastIndex1 - 1] != st2[lastIndex2 - 1])
		extraStep++;

	int cutLeft = RecurseDistMemDamerau(st1, st2, lastIndex1 - 1, lastIndex2,mat) + 1;
	int cutRight = RecurseDistMemDamerau(st1, st2, lastIndex1, lastIndex2 - 1,mat) + 1;
	int cutBoth = RecurseDistMemDamerau(st1, st2, lastIndex1 - 1, lastIndex2 - 1,mat) + extraStep;
	int DamerauCut = cutBoth + 1;
	if (lastIndex1 > 1 && lastIndex2 > 1 && st1[lastIndex1 - 2] == st2[lastIndex2 - 1]
		&& st1[lastIndex1 - 1] == st2[lastIndex2 - 2])
		DamerauCut = RecurseDistMemDamerau(st1, st2, lastIndex1 - 2, lastIndex2 - 2,mat) + 1;
	cutBoth = std::min(DamerauCut, cutBoth);
	int chosenOne = std::min(std::min(cutRight, cutLeft), cutBoth);
	mat._table[lastIndex1][lastIndex2] = chosenOne;
	return chosenOne;
}

size_t Matrix::findRecurseDistMemDamerau(const std::wstring& st1, const std::wstring& st2)
{
	for (int i = 0; i < _n; i++)
		for (int j = 0; j < _m; j++)
			_table[i][j] = INF;

	return RecurseDistMemDamerau(st1, st2, st1.size(), st2.size(), *this);
}

size_t Matrix::findRecurseDistDamerau(const std::wstring& st1, const std::wstring& st2)
{
	return RecurseDistDamerau(st1, st2, st1.size(), st2.size());
}




