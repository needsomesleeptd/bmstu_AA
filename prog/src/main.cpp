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
	AtomicQueue<Request> start;
	AtomicQueue<Request> end;
	int n = 100;
	int numsCount = 51;
	for (int i = 0; i < n -1;i++)
	{
		Request request;
		request.id = i;
		request.req = generateVector(numsCount);
		start.push(request);
	}
	Request request;
	request.id = n;
	request.req = generateVector(numsCount);
	request.is_last = true;
	start.push(request);
	StartConveyor(start,end);






}