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
	StartConveyor(start,end);


}