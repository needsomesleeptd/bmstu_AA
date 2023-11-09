//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "sort.hpp"
#include "cassert"
#include <algorithm>




void blockSort(std::vector<int> &arr, int blockSize)
{
	std::vector<std::vector<int> > blocks;

	// Divide the input array into blocks of size blockSize
	for (size_t i = 0; i < arr.size(); i += blockSize) {
		std::vector<int> block;

		for (size_t j = i; j < i + blockSize && j < arr.size();
		     j++) {
			block.push_back(arr[j]);
		}

		// Sort each block and append it to the list of
		// sorted blocks
		//vector<int> second(block.begin(), block.begin() + 1);
		shakerSort(block);

		blocks.push_back(block);
	}

	// Merge the sorted blocks into a single sorted list
	std::vector<int> result;
	while (!blocks.empty()) {
		// Find the smallest element in the first block of
		// each sorted block
		int minIdx = 0;
		for (size_t i = 1; i < blocks.size(); i++) {
			if (blocks[i][0] < blocks[minIdx][0]) {
				minIdx = i;
			}
		}

		// Remove the smallest element and append it to the
		// result list
		result.push_back(blocks[minIdx][0]);
		blocks[minIdx].erase(blocks[minIdx].begin());

		// If the block is now empty, remove it from the
		// list of sorted blocks
		if (blocks[minIdx].empty()) {
			blocks.erase(blocks.begin() + minIdx);
		}
	}

	arr = result;
}


void shakerSort(std::vector<int>& arr)
{
	int control = arr.size() - 1;
	int left = 0, right = control;
	do
	{
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				std::swap(arr[i], arr[i + 1]);
				control = i;
			}
		}
		right = control;
		for (int i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				std::swap(arr[i], arr[i - 1]);
				control = i;
			}
		}
		left = control;
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


