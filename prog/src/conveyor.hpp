#include <vector>
#include <string>
#include "atomic_queue.h"
#include "sorts.h"
#include "timings.h"

const int maxQueues  = 3;

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



timespec getTime();
void StartConveyor(AtomicQueue<Request>& start, AtomicQueue<Request>& end);
void createReport(Request& req);
