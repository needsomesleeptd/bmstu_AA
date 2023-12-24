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