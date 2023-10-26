//
// Created by Андрей on 21/10/2023.
//


#include <random>
#include <iostream>
#include <wchar.h>

#include "timings.h"
#include "table.hpp"

const double TIMEDIVISION = 1e6; //Millisecounds
const int MAXVAL = 1e4;

Matrix generateMatrix(const size_t len)
{
	srand(time(NULL));
	Matrix mat(len,len);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0,1e4);
	for (size_t i = 0; i < len; i++)
		for (size_t j =0; j < len; j++)
			mat._table[i][j] = dist(rng);


	return mat;
}

long getCpuTime()
{
	struct timespec t;
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
		std::cerr << "Impossible to get time\n";
		return -1;
	}
	return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double getCPUTimeSTD(const Matrix &mat1, const Matrix &mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeVin(const Matrix &mat1, const Matrix &mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_vin(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeVinOpt(const Matrix &mat1, const Matrix &mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_vin_opt(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeStrassen(const Matrix &mat1, const Matrix &mat2)
{
	long startTime;
	long endTime;
	//double overallTime;
	startTime = getCpuTime();
	mat1.dot_shtrassen(mat2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

void getTimeResultsMatrix(size_t wordsLen,int countProcessed)
{


	Matrix mat1 = generateMatrix(wordsLen);
	Matrix mat2 = generateMatrix(wordsLen);

	double STDTime = 0.0;
	double STRASSENTime = 0.0;
	double VINTime = 0.0;
	double VINOPTTime = 0.0;
	for (int i = 0; i < countProcessed ;++i)
	{
		STDTime += getCPUTimeSTD(mat1,mat2);
		STRASSENTime += getCPUTimeStrassen(mat1,mat2);
		VINTime += getCPUTimeVin(mat1,mat2);
		VINOPTTime += getCPUTimeVinOpt(mat1,mat2);
	}
	STDTime /= countProcessed;
	STRASSENTime /= countProcessed;
	VINTime /= countProcessed;
	VINOPTTime /= countProcessed;
	wprintf(L"|%7zu||%25.5g||%28.5g||%32.5g||%29.5g|\n",wordsLen,STDTime,STRASSENTime,VINTime,VINOPTTime);
	std::cout << std::flush;
}

void getMemResultsWord(size_t wordsLen,int countProcessed)
{


	/*std::wstring st1 = generateString(wordsLen);
	std::wstring st2 = generateString(wordsLen);
	Matrix mat(st1.size(),st2.size());

	size_t matrixSize = sizeof(Matrix)  + (wordsLen + 1) * (wordsLen + 1) * sizeof(int);

	size_t damerauMatrix = matrixSize + sizeof(Matrix&) +  2 * (wordsLen * sizeof(wchar_t)
		+ sizeof(std::wstring) + sizeof(std::wstring&)) + sizeof(int);

	size_t damerauRec = (wordsLen + wordsLen) *  (2 * sizeof(std::wstring&) + sizeof(int) + 6 * sizeof(size_t))
		+ 2 * (wordsLen * sizeof(wchar_t) + sizeof(std::wstring));

	size_t damerauRecMem = (wordsLen + wordsLen) *  (2 * sizeof(std::wstring&) + sizeof(int) + 6 * sizeof(size_t) + sizeof(Matrix&))
		+ 2 * (wordsLen * sizeof(wchar_t) + sizeof(std::wstring)) + matrixSize + sizeof(Matrix&);

	size_t levMatrix = matrixSize + sizeof(Matrix&) +  2 * (wordsLen * sizeof(wchar_t)
		+ sizeof(std::wstring) + sizeof(std::wstring&)) + sizeof(int);

	wprintf(L"|%7zu||%20zu||%23zu||%27zu||%24zu|\n",wordsLen,damerauMatrix,damerauRec,damerauRecMem,levMatrix);
	std::cout << std::flush;*/
}






void getMemResults(size_t wordLenStart,size_t wordLenStop,size_t wordLenStep,int countProcessed)
{
	wprintf(L"\n\n|   n   ||   DamerauMatrix    ||   DamerauRecursion    ||  DamerauMemoryRecursion   ||    LevenshteinMatrix   |\n");
	for (size_t i = wordLenStart; i < wordLenStop; i+= wordLenStep)
	{
		getMemResultsWord(i,countProcessed);
	}
}
void getTimeResults(size_t wordLenStart,size_t wordLenStop,size_t wordLenStep,int countProcessed)
{
	wprintf(L"\n\n|   n   ||   STD(mcs)    ||   Strassen(mcs)    ||  Vinograd(mcs)   ||    VinogradOptimized(mcs)   |\n");
	for (size_t i = wordLenStart; i < wordLenStop; i += wordLenStep)
	{
		getTimeResultsMatrix(i, countProcessed);
	}
}