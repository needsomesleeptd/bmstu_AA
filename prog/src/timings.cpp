//
// Created by Андрей on 10/09/2023.
//
#include "find.hpp"

#include <random>
#include <iostream>
#include <algorithm>

#include "timings.h"

const double TIMEDIVISION = 1e6; //Millisecounds
const int MAXVAL = 1e4;

std::vector<int> generateVector(const size_t len)
{
	srand(time(NULL));
	std::vector<int> vec(len);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1e7);
	for (size_t i = 0; i < len; i++)
		vec[i] = dist(rng);
	std::sort(vec.begin(), vec.end());
	return vec;
}

long getCpuTime()
{
	struct timespec t;
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t))
	{
		std::cerr << "Impossible to get time\n";
		return -1;
	}
	return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double getCPUTimeRadix(std::vector<int>& vec)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
//	radixSort(vec);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeBlock(std::vector<int>& vec)
{
	int k = vec.size() / 2 + 2;
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	//blockSort(vec, k);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeShaker(std::vector<int>& vec)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	//shakerSort(vec);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

void getTimeResultsMatrix(size_t wordsLen,
	int countProcessed,
	std::vector<std::vector<std::pair<int, int>>>& resultBF,
	std::vector<std::vector<std::pair<int, int>>>& resultF)
{
	std::vector<std::vector<std::pair<int, int>>> mergedBFind;
	std::vector<std::vector<std::pair<int, int>>> mergedFind;

	std::vector<int> nums = generateVector(wordsLen);
	std::vector<std::pair<int, int>> tempBF;
	std::vector<std::pair<int, int>> tempF;

	search(nums, -1, tempF);
	binSearch(nums, -1, tempBF);
	mergedBFind.push_back(tempBF);
	mergedFind.push_back(tempF);
	tempBF.clear();
	tempF.clear();

	for (int i = 0; i < wordsLen; i++)
	{
		search(nums, nums[i], tempF);
		binSearch(nums, nums[i], tempBF);
		mergedBFind.push_back(tempBF);
		mergedFind.push_back(tempF);
		tempBF.clear();
		tempF.clear();
	}



	resultF = mergedFind;
	resultBF = mergedBFind;
}


