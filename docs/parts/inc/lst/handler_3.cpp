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