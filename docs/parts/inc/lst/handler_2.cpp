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
