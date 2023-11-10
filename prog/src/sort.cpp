//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "sort.hpp"
#include "cassert"
#include <algorithm>

void blockSort(std::vector<int>& arr, int blockSize)
{
	std::vector<std::vector<int> > blocks;

	for (size_t i = 0; i < arr.size(); i += blockSize)
	{
		std::vector<int> block;

		for (size_t j = i; j < i + blockSize && j < arr.size();
		     j++)
		{
			block.push_back(arr[j]);
		}

		shakerSort(block);
		blocks.push_back(block);
	}

	int arrIndex = 0;
	while (!blocks.empty())
	{

		int minIdx = 0;
		for (size_t i = 1; i < blocks.size(); i++)
		{
			if (blocks[i][0] < blocks[minIdx][0])
			{
				minIdx = i;
			}
		}

		arr[arrIndex] = blocks[minIdx][0];
		arrIndex++;
		blocks[minIdx].erase(blocks[minIdx].begin());

		if (blocks[minIdx].empty())
		{
			blocks.erase(blocks.begin() + minIdx);
		}
	}

}

void shakerSort(std::vector<int>& arr)
{
	//int control = arr.size() - 1;
	int left = 0, right = arr.size() - 1;
	do
	{
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				std::swap(arr[i], arr[i + 1]);
				//control = i;
			}
		}
		right -= 1;
		for (int i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				std::swap(arr[i], arr[i - 1]);
				//control = i;
			}
		}
		left += 1;
	} while (left < right);
}

int getMaxAbs(const std::vector<int>& arr)
{
	int mx = abs(arr[0]);
	for (size_t i = 1; i < arr.size(); i++)
		if (arr[i] > abs(mx))
			mx = arr[i];
	return mx;
}

void countSort(std::vector<int>& arr, int exp)
{

	int n = arr.size();
	int output[n];
	int count[20] = { 0 };
	int i;

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10 + 9]++;

	for (i = 1; i < 20; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10 + 9] - 1] = arr[i];
		count[(arr[i] / exp) % 10 + 9]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];

}

void radixSort(std::vector<int>& arr)
{

	int m = getMaxAbs(arr);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, exp);
}


