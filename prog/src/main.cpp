#include <iostream>
#include <string>
#include "conveyor.hpp"
#include <locale>

#include "timings.h"
#include "atomic_queue.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Сортировка массива с использованием сортировки перемешивания\n"
                   "2)Сортировка массива с использованием поразрядной сортировки\n"
                   "3)Сортировка массива с использованием блочной сортировки\n"
                   "4)Расчет времени\n";
int main()
{
	std::queue<Request> ref; // those ones are not atomic because there is no race
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
	Linear(start,end);






}