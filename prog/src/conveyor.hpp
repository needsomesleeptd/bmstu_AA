#include <vector>
#include <string>
#include "atomic_queue.h"

struct Request
{
	int id;
	timespec time_start_1;
	timespec time_end_1;
	timespec time_start_2;
	timespec time_end_2;
	std::vector<int> req;

};

timespec getTime();
void StartConveyor(AtomicQueue<Request>& start, AtomicQueue<Request>& end);
