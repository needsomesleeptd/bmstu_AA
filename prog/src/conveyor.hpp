#include <vector>
#include <string>
#include "atomic_queue.h"
#include "sorts.h"
//#include "timings.h"

const int maxQueues  = 3;
const double MIL = 1e6;

struct Request
{
	int id;
	bool  is_last;
	timespec time_start_1;
	timespec time_end_1;
	timespec time_start_2;
	timespec time_end_2;
	std::vector<int> req;

};

double getTimeQ(std::queue<Request> st);
void createReport( std::queue<Request>& requests);
timespec getTime();
void StartConveyorAsync(std::queue<Request>& start, std::queue<Request>& end);
void StartConveyorLinear(std::queue<Request>& start, std::queue<Request>& end);
void Linear(std::queue<Request>& startQ, std::queue<Request>& endQ);
void dumpInFile(Request& req, const std::string& folderName = "../out/");
void createReport(Request& req);
void fillQueue(std::queue<Request> &q, int req, int n);
double diff_timespec(const timespec& time1, const timespec& time0);