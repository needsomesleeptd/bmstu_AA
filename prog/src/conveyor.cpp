

#include "conveyor.hpp"
#include "sorts.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include <valarray>

#include <random>
#include <iostream>
#include <fstream>

#include "atomic_queue.h"


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

void handle_first(std::queue<Request>& from, std::queue<Request>& to)
{
	timespec start, end;
	Request curRequest = from.front();
	from.pop();
	std::vector<int> copy = curRequest.req;
	start = getTime();
	mergeSort(copy, 0, copy.size() - 1);
	end = getTime();
	curRequest.time_start_1 = start;
	curRequest.time_end_1 = end;
	to.push(curRequest);
}

void handle_secound(std::queue<Request>& from, std::queue<Request>& to)
{
	timespec start, end;
	Request curRequest = from.front();
	from.pop();
	std::vector<int> copy = curRequest.req;
	start = getTime();
	mergeSortMultiThread(copy, 0, copy.size() - 1, 4);
	end = getTime();
	curRequest.time_start_2 = start;
	curRequest.time_end_2 = end;
	to.push(curRequest);
}

void write_into_file(Request& req, const std::string& folderName = "out/")
{
	std::ofstream out(folderName + std::to_string(req.id));
	std::vector<int> vec = req.req;
	for (int i = 0; i < vec.size(); i++)
		out << vec[i] << " ";

}

void handle_third(std::queue<Request>& from, std::queue<Request>& endQ)
{
	timespec start, end;
	Request curRequest = from.front();
	from.pop();
	write_into_file(curRequest);
	endQ.push(curRequest);

}

int start_conveyor(std::queue<Request>& start, std::vector<Request>& end)
{
	std::queue<Request> secondQ;
	std::queue<Request> thirdQ;
	handle_first(start,secondQ);
	handle_secound(secondQ,thirdQ);
	handle_third(thirdQ, end);
}

timespec getTime()
{
	timespec start;

	clock_gettime(CLOCK_REALTIME, &start);
	return start; // in Millisecounds
}

void handle_secound(std::queue<Request>& requests)
{

}




