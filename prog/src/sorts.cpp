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

void mergeSort(std::vector<int> & arr, int left, int right)
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








void mergeSortMultiThread(std::vector<int>& nums, int s, int e, int availThreads)
{
	if (s >= e)
	{
		return;
	}

	int mid = (s + e) / 2;
	if (availThreads >= 2)
	{
		std::thread t1(std::bind(mergeSortMultiThread, std::ref(nums), s, mid, availThreads / 2));
		std::thread t2(std::bind(mergeSortMultiThread, std::ref(nums), mid + 1, e, availThreads / 2));
		t1.join();
		t2.join();
	}
	else
	{
		mergeSortMultiThread(nums, s, mid, 1);
		mergeSortMultiThread(nums, mid + 1, e, 1);
	}
	merge(nums, s, mid, e);
}




