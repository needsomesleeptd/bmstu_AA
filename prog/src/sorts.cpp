//
// Created by Андрей on 10/09/2023.
//


#include <random>
#include <iostream>
#include <thread>
#include <functional>
#include "sorts.h"

/*void printVector(const std::vector<int>& a)
{
	for (int i : a)
		std::cout << i << ' ';
}*/

void merge(std::vector<int>& nums, int s, int mid, int e)
{
	std::vector<int> lnums, rnums;
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
	int mid = (left + right) / 2;
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
	if (availThreads == 1)
	{
		std::thread t(std::bind(mergeSortMultiThread, std::ref(nums), s, mid, 0));
		mergeSortMultiThread(nums, mid + 1, e, 0);
		t.join();
	}
	else if (availThreads >= 2)
	{
		int oddThread = (availThreads % 2);
		std::thread t1(std::bind(mergeSortMultiThread, std::ref(nums), s, mid, availThreads / 2 + oddThread));
		std::thread t2(std::bind(mergeSortMultiThread, std::ref(nums), mid + 1, e, availThreads / 2));
		t1.join();
		t2.join();
	}
	else
	{
		mergeSortMultiThread(nums, s, mid, 0);
		mergeSortMultiThread(nums, mid + 1, e, 0);
	}
	merge(nums, s, mid, e);
}



