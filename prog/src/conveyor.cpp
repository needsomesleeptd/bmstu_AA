

#include "conveyor.hpp"
#include "sorts.h"

#include <vector>
#include <iostream>

#include <ctime>
#include <algorithm>

#include <fstream>
#include <thread>
#include <functional>

void handle_first(AtomicQueue<Request>& from, AtomicQueue<Request>& to)
{
	bool isWorking = true;
	while (isWorking)
	{
		if (from.size() > 0)
		{
			timespec start, end;
			Request curRequest = from.front();

			if (curRequest.is_last)
				isWorking = false;

			from.pop();
			std::vector<int> copy = curRequest.req;
			start = getTime();
			mergeSort(copy, 0, copy.size() - 1);
			end = getTime();

			curRequest.time_start_1 = start;
			curRequest.time_end_1 = end;
			to.push(curRequest);
		}

	}

}

void handle_second(AtomicQueue<Request>& from, AtomicQueue<Request>& to)
{
	bool isWorking = true;
	while (isWorking)
	{
		if (from.size() > 0)
		{
			timespec start, end;
			Request curRequest = from.front();
			from.pop();
			if (curRequest.is_last)
				isWorking = false;

			std::vector<int> copy = curRequest.req;
			start = getTime();
			mergeSortMultiThread(copy, 0, copy.size() - 1, 4);
			end = getTime();
			curRequest.time_start_2 = start;
			curRequest.time_end_2 = end;
			to.push(curRequest);
		}
	}
}

void write_into_file(Request& req, const std::string& folderName = "out/")
{
	std::ofstream out(folderName + std::to_string(req.id));
	std::vector<int> vec = req.req;
	for (int i = 0; i < vec.size(); i++)
		out << vec[i] << " ";

}

void handle_third(AtomicQueue<Request>& from, AtomicQueue<Request>& endQ)
{

	bool isWorking = true;
	while (isWorking)
	{
		if (from.size() > 0)
		{
			Request curRequest = from.front();
			from.pop();
			if (curRequest.is_last)
				isWorking = false;

			write_into_file(curRequest);
			endQ.push(curRequest);
		}
	}

}

void StartConveyor(AtomicQueue<Request>& start, AtomicQueue<Request>& end)
{
	AtomicQueue<Request> secondQ;
	AtomicQueue<Request> thirdQ;
	//handle_first(start, secondQ);
	//handle_second(secondQ, thirdQ);
	//handle_third(thirdQ, end);
	std::thread t1(std::bind(handle_first, std::ref(start), std::ref(secondQ)));
	std::thread t2(std::bind(handle_second, std::ref(secondQ), std::ref(thirdQ)));
	std::thread t3(std::bind(handle_third, std::ref(thirdQ), std::ref(end)));
	t1.join();
	t2.join();
	t3.join();
	//handle_second(secondQ, thirdQ);
	//handle_third(thirdQ, end);
}

timespec getTime()
{
	timespec start;

	clock_gettime(CLOCK_REALTIME, &start);
	return start;
}

void createReport( AtomicQueue<Request>& requests)
{

}
