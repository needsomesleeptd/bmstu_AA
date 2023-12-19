//
// Created by Андрей on 05/09/2023.
//

#include <iostream>
#include "find.hpp"
#include "cassert"
#include <algorithm>

int binSearch(std::vector<int>& v, int x, std::vector<std::pair<int,int>>& res)
{
	int low = 0;
	int high = (int)v.size() - 1;
	int cmpCount = 0;
	while (low <= high)
	{
		++cmpCount;
		int mid = (high + low) / 2;
		res.emplace_back(mid,cmpCount);
		++cmpCount;

		if (v[mid] == x)
			return mid;

		if (v[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}
	++cmpCount;

	return -1;

}
int search(std::vector<int>& v, int x, std::vector<std::pair<int,int>>& res)
{

	int cmpCount = 0;
	for (int i = 0; i < v.size(); i++)
	{
		++cmpCount;
		res.emplace_back(i,cmpCount);
		if (v[i] == x)
			return i;
	}
	return -1;
}