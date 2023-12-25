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
}