//
// Created by Андрей on 10/09/2023.
//
#include "sorts.h"

#include <random>
#include <iostream>

#include "measure.h"

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

double getCPUTimeMerge(std::vector<int>& vec)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mergeSort(vec, 0, vec.size() - 1);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeMergeMultiThread(std::vector<int>& vec, int threadCount)
{

	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mergeSortMultiThread(vec, 0, vec.size() - 1, threadCount);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getTimeResultsMatrix(size_t wordsLen,
	int countProcessed,
	std::vector<int>& result,
	int threadCount,
	double mergeTimePrev)
{

	std::vector<int> vec(wordsLen);
	for (size_t i = 0; i < wordsLen; i++)
		vec[i] = result[i];

	double mergeSortTime = 0.0;
	double mergeSortTimeMultiThread = 0.0;

	for (int i = 0; i < countProcessed; ++i)
	{
		std::vector<int> vec_test = vec;
		if (mergeTimePrev < 0.0)
			mergeSortTime += getCPUTimeMerge(vec_test);
		vec_test = vec;
		mergeSortTimeMultiThread += getCPUTimeMergeMultiThread(vec_test, threadCount);

	}
	if (mergeTimePrev < 0.0)
		mergeSortTime /= countProcessed;
	else
		mergeSortTime = mergeTimePrev;
	mergeSortTimeMultiThread /= countProcessed;

	printf("|%7zu||%15.5g||%18.5g|%3d|\n", wordsLen, mergeSortTime, mergeSortTimeMultiThread, threadCount);
	std::cout << std::flush;
	return mergeSortTime;
}

void getTimeResults(size_t wordLenStart,
	size_t wordLenStop,
	size_t wordLenStep,
	int countProcessed,
	int threadCountStart,
	int threadCountEnd)
{
	printf("\n\n|   n   ||   Сортировка слиянием(мс)    ||   Сортировка Слияние многопоток(мс)    ||  число потоков|\n");
	std::vector<int> res = generateVector(wordLenStop);
	double prevTime;
	for (size_t i = wordLenStart; i < wordLenStop; i += wordLenStep)
	{
		prevTime = -1.0;
		for (int thr = threadCountStart; thr < threadCountEnd; ++thr)
			prevTime = getTimeResultsMatrix(i, countProcessed, res, thr, prevTime);

	}
}