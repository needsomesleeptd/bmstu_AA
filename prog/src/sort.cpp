//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "sort.hpp"
#include "cassert"

int block_sort(std::vector<int>& p, int bucket_count)
{
	std::vector<int> temp[bucket_count];

	for (int i = 0; i < bucket_count; i++)
	{
		int bi = bucket_count * p[i]; // Index in bucket
		temp[bi].push_back(p[i]);
	}

	// 3) Sort individual buckets
	for (int i = 0; i < bucket_count; i++)
		block_sort(temp[i],bucket_count);

	// 4) Concatenate all buckets into arr[]
	int index = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
}

