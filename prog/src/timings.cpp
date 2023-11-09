//
// Created by Андрей on 21/10/2023.
//


#include <random>
#include <iostream>
#include <wchar.h>
#include <stdio.h>

#include "timings.h"
#include "table.hpp"

const double TIMEDIVISION = 1e6; //Millisecounds
const int MAXVAL = 1e4;

Matrix generateMatrix(const size_t len)
{
	srand(time(NULL));
	Matrix mat(len, len);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1e4);
	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len; j++)
			mat._table[i][j] = dist(rng);

	return mat;
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

double getCPUTimeSTD(const Matrix& mat1, const Matrix& mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeVin(const Matrix& mat1, const Matrix& mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_vin(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeVinOpt(const Matrix& mat1, const Matrix& mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_vin_opt(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeStrassen(const Matrix& mat1, const Matrix& mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_shtrassen(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

void getTimeResultsMatrix(size_t wordsLen, int countProcessed)
{

	Matrix mat1 = generateMatrix(wordsLen);
	Matrix mat2 = generateMatrix(wordsLen);

	double STDTime = 0.0;
	double STRASSENTime = 0.0;
	double VINTime = 0.0;
	double VINOPTTime = 0.0;
	for (int i = 0; i < countProcessed; ++i)
	{
		STDTime += getCPUTimeSTD(mat1, mat2);
		STRASSENTime += getCPUTimeStrassen(mat1, mat2);
		VINTime += getCPUTimeVin(mat1, mat2);
		VINOPTTime += getCPUTimeVinOpt(mat1, mat2);
	}
	STDTime /= countProcessed;
	STRASSENTime /= countProcessed;
	VINTime /= countProcessed;
	VINOPTTime /= countProcessed;
	printf("|%7zu||%15.5g||%20.5g||%18.5g||%29.5g|\n", wordsLen, STDTime, STRASSENTime, VINTime, VINOPTTime);
	std::cout << std::flush;
}

void getTimeResults(size_t wordLenStart, size_t wordLenStop, size_t wordLenStep, int countProcessed)
{
	printf("\n\n|   n   ||   STD(mcs)    ||   Strassen(mcs)    ||  Vinograd(mcs)   ||    VinogradOptimized(mcs)   |\n");
	for (size_t i = wordLenStart; i < wordLenStop; i += wordLenStep)
	{
		getTimeResultsMatrix(i, countProcessed);
	}
}