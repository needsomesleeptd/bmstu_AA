//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "sort.hpp"
#include "cassert"
#include <algorithm>

void blockSort(std::vector<int>& arr, int block_size)
{
	int n = arr.size();
	int num_blocks = (n + block_size - 1) / block_size;

	for (int i = 0; i < num_blocks; i++)
	{
		int start = i * block_size;
		int end = std::min(start + block_size, n);
		std::sort(arr.begin() + start, arr.begin() + end);
	}
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

int getMax(const std::vector<int>& arr)
{
	int mx = arr[0];
	for (size_t i = 1; i < arr.size(); i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort(std::vector<int> &arr, int exp)
{

	// Output array
	size_t n = arr.size();
	int output[n];
	int  count[10] = { 0 };
	size_t i;

	// Store count of occurrences
	// in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i]
	// now contains actual position
	// of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[],
	// so that arr[] now contains sorted
	// numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(std::vector<int> &arr)
{

	int m = getMax(arr);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, exp);
}


