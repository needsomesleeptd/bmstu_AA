//
// Created by Андрей on 10/09/2023.
//
#include "sort.hpp"
#include <random>
#include <iostream>
#include <wchar.h>
const double TIMEDIVISION = 1e6; //Millisecounds


std::wstring generateString(const size_t len)
{
	srand(time(NULL));
	std::wstring src = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
					   "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	std::wstring res;
	res.resize(len);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0,src.size() - 1);
	for (size_t i = 0; i < len; i++)
		res[i] = src[dist(rng)];

	return res;
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

double getCPUTimeMatDamerau(const std::wstring &st1,const std::wstring &st2,Matrix& mat)
{
	long startTime;
	long endTime;
	//double overallTime;
	mat = Matrix(st1.size(),st2.size());
	startTime = getCpuTime();
	mat.findMatrixDistDamerau(st1,st2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeRecDamerau(const std::wstring &st1,const std::wstring &st2,Matrix& mat)
{
	long startTime;
	long endTime;
	//double overallTime;
	mat = Matrix(st1.size(),st2.size());
	startTime = getCpuTime();
	mat.findRecurseDistDamerau(st1,st2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeRecMemDamerau(const std::wstring &st1,const std::wstring &st2,Matrix& mat)
{
	long startTime;
	long endTime;
	//double overallTime;
	mat = Matrix(st1.size(),st2.size());
	startTime = getCpuTime();
	mat.findRecurseDistMemDamerau(st1,st2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

double getCPUTimeRecLev(const std::wstring &st1,const std::wstring &st2,Matrix& mat)
{
	long startTime;
	long endTime;
	//double overallTime;
	mat = Matrix(st1.size(),st2.size());
	startTime = getCpuTime();
	mat.findMatrixDistLev(st1,st2);
	endTime = getCpuTime();
	return (endTime - startTime) / TIMEDIVISION;
}

void getTimeResultsWord(size_t wordsLen,int countProcessed)
{

	const int wordLenMax = 12;
	std::wstring st1 = generateString(wordsLen);
	std::wstring st2 = generateString(wordsLen);
	Matrix mat(st1.size(),st2.size());
	double damerauMatrix = 0.0;
	double damerauRec = 0.0;
	double damerauRecMem = 0.0;
	double levMatrix = 0.0;
	for (int i = 0; i < countProcessed ;++i)
	{
		damerauMatrix += getCPUTimeMatDamerau(st1,st2,mat);
		if (wordsLen > wordLenMax)
			damerauRec = -1.0;
		else
			damerauRec += getCPUTimeRecDamerau(st1,st2,mat);
		damerauRecMem += getCPUTimeRecMemDamerau(st1,st2,mat);
		levMatrix += getCPUTimeRecLev(st1,st2,mat);
	}
	damerauMatrix /= countProcessed;
	damerauRec /= countProcessed;
	damerauRecMem /= countProcessed;
	levMatrix /= countProcessed;
	wprintf(L"|%7zu||%25.5g||%28.5g||%32.5g||%29.5g|\n",wordsLen,damerauMatrix,damerauRec,damerauRecMem,levMatrix);
	std::cout << std::flush;
}

void getMemResultsWord(size_t wordsLen,int countProcessed)
{


	std::wstring st1 = generateString(wordsLen);
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
	std::cout << std::flush;
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
	wprintf(L"\n\n|   n   ||   DamerauMatrix(mcs)    ||   DamerauRecursion(mcs)    ||  DamerauMemoryRecursion(mcs)   ||    LevenshteinMatrix(mcs)   |\n");
	for (size_t i = wordLenStart; i < wordLenStop; i+= wordLenStep)
	{
		getTimeResultsWord(i,countProcessed);
	}
}







