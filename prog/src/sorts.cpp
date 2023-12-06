//
// Created by Андрей on 10/09/2023.
//


#include <random>
#include <iostream>
#include <thread>
#include <functional>
#include "sorts.h"

void printVector(const std::vector<int>& a)
{
	for (int i : a)
		std::cout << i << ' ';
}

void merge(std::vector<int>& nums, int s, int mid, int e)
{
	std::vector<int> lnums, rnums; // lnums, rnums are two subsequences, nums is used to store the combined sequence
	for (int i = s; i <= e; i++)
	{
		if (i <= mid)
		{
			lnums.push_back(nums[i]);
		}
		else
		{
			rnums.push_back(nums[i]);
		}
	}

	int l = 0, r = 0, k = s;
	// Compare the elements pointed to by the two pointers (l and r), select relatively small elements (in ascending order) and put them into the merge space,
	// and move the pointer to the next position until one of the pointers exceeds the end of the sequence
	while (l < lnums.size() && r < rnums.size())
	{
		if (lnums[l] < rnums[r])
		{
			nums[k++] = lnums[l++];
		}
		else
		{
			nums[k++] = rnums[r++];
		}
	}
	// Copy all the remaining elements of another sequence directly to the end of the merged sequence
	while (l < lnums.size())
	{
		nums[k++] = lnums[l++];
	}
	while (r < rnums.size())
	{
		nums[k++] = rnums[r++];
	}
}

void mergeSort(std::vector<int>& arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	merge(arr, left, mid, right);
}

void mergeKArrays(std::vector<int>& nums,
	std::vector<std::tuple<int, int>> sortedIndices,
	int i,
	int j,
	int availThreads)
{
	int l = i * std::get<0>(sortedIndices[i]);
	int r = j * std::get<1>(sortedIndices[j]);
	int mid = std::get<1>(sortedIndices[i]);
	if (j - i == 1)
	{
		merge(nums, l, mid, r);
		return;
	}

	mergeKArrays(nums, sortedIndices, i / 2, (i + j) / 2, availThreads / 2);
	mergeKArrays(nums, sortedIndices, (i + j) / 2 + 1, j, availThreads / 2);
	merge(nums, l, mid, r);

}

void mergeSortMultiThread(std::vector<int>& nums, int s, int e, int availThreads)
{
	if (s >= e)
	{
		return;
	}

	std::vector<int> indexes(availThreads);
	std::vector<std::thread> threads(availThreads);
	int elem_delta = (e - s + 1) / availThreads;
	int l = 0;
	int r = elem_delta;
	std::vector<std::tuple<int, int>> sortedIndices;
	for (int i = 0; i < availThreads; i++)
	{

		threads[i] = std::thread(std::bind(mergeSort, std::ref(nums), l, r));
		sortedIndices.emplace_back(l, r);
		l += elem_delta + 1;
		r += elem_delta;
		if (i == availThreads - 2)
			r = nums.size() - 1;

	}

	for (auto& t : threads)
	{
		t.join();
	}

	mergeKArrays(nums, sortedIndices, 0, availThreads - 1, availThreads);
}



