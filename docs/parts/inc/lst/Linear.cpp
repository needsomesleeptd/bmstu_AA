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
}