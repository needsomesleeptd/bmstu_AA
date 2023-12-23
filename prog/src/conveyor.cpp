

#include "conveyor.hpp"
#include "sorts.h"

#include <vector>
#include <iostream>

#include <ctime>
#include <algorithm>

#include <fstream>





void handle_first(AtomicQueue<Request>& from, AtomicQueue<Request>& to)
{
	timespec start, end;
	Request curRequest = from.front();
	from.pop();
	std::vector<int> copy = curRequest.req;
	start = getTime();
	mergeSort(copy, 0, copy.size() - 1);
	end = getTime();
	char buff[100];
	strftime(buff, sizeof buff, "%D %T", gmtime(&start.tv_sec));
	printf("Start time: %s.%09ld UTC\n", buff, start.tv_nsec);

	strftime(buff, sizeof buff, "%D %T", gmtime(&start.tv_sec));
	printf("end time: %s.%09ld UTC\n", buff, start.tv_nsec);


	//std::cout << start << " " << end << std::endl;
	curRequest.time_start_1 = start;
	curRequest.time_end_1 = end;
	to.push(curRequest);
}

void handle_second(AtomicQueue<Request>& from, AtomicQueue<Request>& to)
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

void handle_third(AtomicQueue<Request>& from, AtomicQueue<Request>& endQ)
{
	timespec start, end;
	Request curRequest = from.front();
	from.pop();
	write_into_file(curRequest);
	endQ.push(curRequest);

}

void StartConveyor(AtomicQueue<Request>& start, AtomicQueue<Request>& end)
{
	AtomicQueue<Request> secondQ;
	AtomicQueue<Request> thirdQ;
	handle_first(start,secondQ);
	handle_second(secondQ, thirdQ);
	handle_third(thirdQ, end);
}

timespec getTime()
{
	timespec start;

	clock_gettime(CLOCK_REALTIME, &start);
	return start; // in Millisecounds
}






