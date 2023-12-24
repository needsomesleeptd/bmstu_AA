#include <iostream>
#include <string>
#include "conveyor.hpp"
#include <locale>

#include "timings.h"
#include "atomic_queue.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Запустить последовательную обработку массивов\n"
                   "2)Запустить конвейерную обработку массивов\n"
                   "3)Замеры времени реализаций\n";
int main()
{

	/*std::queue<Request> ref; // those ones are not atomic because there is no race
	std::queue<Request> end;
	int n = 20;
	int numsCount = 510;
	for (int i = 0; i < n -1;i++)
	{
		Request request;
		request.id = i;
		request.req = generateVector(numsCount);
		ref.push(request);
	}
	Request request;
	request.id = n;
	request.req = generateVector(numsCount);
	request.is_last = true;
	ref.push(request);
	std::queue<Request> start = ref;
	StartConveyorAsync(start, end);
	std::cout << std::endl;
	start = ref;
	end = std::queue<Request>();
	//StartConveyorLinear(start,end);
	Linear(start,end);*/
	int request = -1;
	while (request != 0)
	{
		std::cout << menu << "\n";
		std::cout << "Введите пункт из меню: ";
		std::cin >> request;
		std::cout << "\n";
		if (request == 0)
			break;
		if (1 <= request && request <= 2)
		{
			int n = -1;
			int req = -1;
			while (n <= 0)
			{
				std::cout << "Введите  размер массива для сортировки:\n";
				std::cin >> n;
				if (n <= 0)
					std::cout << "Введенная размерность массива невалидна\n";

			}

			while (req <= 0)
			{
				std::cout << "Введите число заявок для сортировки:\n";
				std::cin >> req;
				if (req <= 0)
					std::cout << "Введенное число заявок невалидно\n";

			}

			std::queue<Request> startQ;
			std::queue<Request> endQ;
			fillQueue(startQ,req,n);
			switch (request)
			{
			case 1:
				Linear(startQ,endQ);
				break;
			case 2:
				StartConveyorAsync(startQ,endQ);
				break;
			}
			createReport(endQ);
		}
		else
		{
			int start, stop, step;
			int count;
			int startReq, stopReq,stepReq;
			std::cout
				<< "Введите начальный размер массива, конечный размер и шаг изменения размера массива\n";
			std::cin >> start >> stop >> step;
			std::cout << "Введите начальное число заявок, конечное число заявок и шаг изменения числа заявок\n";
			std::cin >> startReq >> stopReq >> stepReq;
			getTimeResults(start, stop, step, startReq, stopReq, stepReq);
		}
	}
	return 0;





}