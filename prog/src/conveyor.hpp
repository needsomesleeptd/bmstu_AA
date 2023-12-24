#include <vector>
#include <string>
#include "atomic_queue.h"
#include "sorts.h"
#include "timings.h"

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


void createReport( std::queue<Request>& requests);
timespec getTime();
void StartConveyorAsync(std::queue<Request>& start, std::queue<Request>& end);
void StartConveyorLinear(std::queue<Request>& start, std::queue<Request>& end);
void Linear(std::queue<Request>& startQ, std::queue<Request>& endQ);
void write_into_file(Request& req, const std::string& folderName = "../out/");
void createReport(Request& req);
