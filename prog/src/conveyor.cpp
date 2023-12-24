

#include "conveyor.hpp"
#include "sorts.h"
#include <queue>

#include <vector>
#include <iostream>

#include <ctime>
#include <algorithm>

#include <fstream>
#include <thread>
#include <functional>

void handle_first_linear(std::queue<Request>& from, std::queue<Request>& to)
{
	while (!from.empty())
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
}

void handle_second_linear(std::queue<Request>& from, std::queue<Request>& to)
{
	while (!from.empty())
	{
		timespec start, end;
		Request curRequest = from.front();
		from.pop();
		start = getTime();
		mergeSortMultiThread(curRequest.req, 0, curRequest.req.size() - 1, 4);
		end = getTime();
		curRequest.time_start_2 = start;
		curRequest.time_end_2 = end;
		to.push(curRequest);
	}
}

void handle_third_linear(std::queue<Request>& from, std::queue<Request>& to)
{
	while (!from.empty())
	{
		Request curRequest = from.front();
		from.pop();
		write_into_file(curRequest);
		to.push(curRequest);
	}
}

void handle_first(std::queue<Request>& from, AtomicQueue<Request>& to)
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
			timespec start{}, end{};
			Request curRequest = from.front();
			from.pop();
			if (curRequest.is_last)
				isWorking = false;

			start = getTime();
			mergeSortMultiThread(curRequest.req, 0, curRequest.req.size() - 1, 4);
			end = getTime();
			curRequest.time_start_2 = start;
			curRequest.time_end_2 = end;
			to.push(curRequest);
		}
	}
}

void write_into_file(Request& req, const std::string& folderName)
{
	std::ofstream out;
	out.open(folderName + std::to_string(req.id));

	std::vector<int> vec = req.req;
	for (int i : vec)
		out << i << " ";
	//std::cout<< vec[0];
	out.close();
}

void handle_third(AtomicQueue<Request>& from, std::queue<Request>& endQ)
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

void StartConveyorLinear(std::queue<Request>& start, std::queue<Request>& end)
{
	std::queue<Request> secondQ;
	std::queue<Request> thirdQ;
	handle_first_linear(start, secondQ);
	handle_second_linear(secondQ, thirdQ);
	handle_third_linear(thirdQ, end);
	createReport(end);

}

void StartConveyorAsync(std::queue<Request>& start, std::queue<Request>& end)
{
	AtomicQueue<Request> secondQ;
	AtomicQueue<Request> thirdQ;

	std::thread t1(std::bind(handle_first, std::ref(start), std::ref(secondQ)));
	std::thread t2(std::bind(handle_second, std::ref(secondQ), std::ref(thirdQ)));
	std::thread t3(std::bind(handle_third, std::ref(thirdQ), std::ref(end)));
	t1.join();
	t2.join();
	t3.join();
	createReport(end);
}

timespec getTime()
{
	timespec start;

	clock_gettime(CLOCK_REALTIME, &start);
	return start;
}

void createReport(std::queue<Request>& requests)
{
	std::cout << "|Delta first|Delta second|\n";
	int requestsCount = requests.size();
	std::cout<< requestsCount << "\n";
	double startTime = 0.0;
	double endTime = 0.0;
	for (int i = 0; i < requestsCount; i++)
	{
		Request req = requests.front();
		requests.pop();
		double deltaFirst = (req.time_end_1.tv_nsec - req.time_start_1.tv_nsec) / MIL;
		double deltaSecond = (req.time_end_2.tv_nsec - req.time_start_2.tv_nsec) / MIL;

		if (i == 0)
			startTime = req.time_end_1.tv_nsec;
		if (i == requestsCount - 1)
			endTime = req.time_end_2.tv_nsec;
		std::cout << "|" << deltaFirst << "|" << deltaSecond << "|\n";
		requests.push(req);
	}
	std:: cout << "delta" << (endTime - startTime) / MIL << std::endl;
}

void Linear(std::queue<Request>& startQ, std::queue<Request>& endQ)
{
	while (!startQ.empty())
	{
		timespec start, end;
		Request curRequest = startQ.front();
		startQ.pop();
		std::vector<int> copy = curRequest.req;
		start = getTime();
		mergeSort(copy, 0, copy.size() - 1);
		end = getTime();
		curRequest.time_start_1 = start;
		curRequest.time_end_1 = end;


		start = getTime();
		mergeSortMultiThread(curRequest.req, 0, curRequest.req.size() - 1, 4);
		end = getTime();
		curRequest.time_start_2 = start;
		curRequest.time_end_2 = end;
		write_into_file(curRequest);
		endQ.push(curRequest);
	}
	createReport(endQ);

}
