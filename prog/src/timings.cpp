//
// Created by Андрей on 10/09/2023.
//
#include "sort.hpp"

#include <random>
#include <iostream>

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
	radixSort(vec);
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
	blockSort(vec, k);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeShaker(std::vector<int>& vec)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	shakerSort(vec);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

void getTimeResultsMatrix(size_t wordsLen, int countProcessed)
{

	std::vector<int> vec = generateVector(countProcessed);
	double Radix = 0.0;
	double STRASSENTime = 0.0;
	double Block = 0.0;
	double Shaker = 0.0;
	for (int i = 0; i < countProcessed; ++i)
	{
		std::vector<int> vec_test = vec;
		Radix += getCPUTimeRadix(vec_test);
		Block += getCPUTimeBlock(vec_test);
		Shaker += getCPUTimeShaker(vec_test);
	}
	Radix /= countProcessed;
	STRASSENTime /= countProcessed;
	Block /= countProcessed;
	Shaker /= countProcessed;
	printf("|%7zu||%15.5g||%18.5g||%29.5g|\n", wordsLen, Radix, Block, Shaker);
	std::cout << std::flush;
}

void getTimeResults(size_t wordLenStart, size_t wordLenStop, size_t wordLenStep, int countProcessed)
{
	printf("\n\n|   n   ||   Поразраядная(mcs)    ||   Блочная(mcs)    ||  Перемешиванием(mcs)   |\n");
	for (size_t i = wordLenStart; i < wordLenStop; i += wordLenStep)
	{
		getTimeResultsMatrix(i, countProcessed);
	}
}

