#include <iostream>
#include <string>
#include "sort.hpp"
#include <locale>
#include "timings.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Сортировка массива с использованием сортировки перемешивания\n"
                   "2)Сортировка массива с использованием поразрядной сортировки\n"
                   "3)Сортировка массива с использованием блочной сортировки\n"
                   "4)Расчет времени\n";

int main()
{

	int request = -1;
	while (request != 0)
	{
		std::cout << menu << "\n";
		std::cout << "Введите пункт из меню: ";
		std::cin >> request;
		std::cout << "\n";
		if (request == 0)
			break;
		if (1 <= request && request <= 3)
		{
			int n = -1;
			while (n <= 0)
			{
				std::cout << "Введите  размер массива для сортировки:\n";
				std::cin >> n;
				if (n <= 0)
					std::cout << "Введенная размерность массива невалидна\n";


			}
			std:: cout << "Введите массив для сортировки:\n";
			std::vector<int> vec(n);
			for (int i = 0; i < n; i++)
			{
				std::cin >> vec[i];
			}

			switch (request)
			{
			case 1:
				shakerSort(vec);
				break;
			case 2:
				radixSort(vec);
				break;
			case 3:
				int k = -1 ;
				while (k <= 0)
				{
					std::cout << "Введите количество блоков в сортировке\n";
					std::cin >> k;
					if (k <= 0)
						std::cout<< "Введенное значение количества блоков невалидно, попробуйте еще раз.\n";
				}
				blockSort(vec, k);
				break;
			}
			std::cout << "Отсортированный массив\n";
			for (size_t i = 0; i < vec.size(); i++)
				std::cout << vec[i] << " ";
			std::cout << '\n';
		}
		else
		{
			int start, stop, step;
			int count;
			std::cout
				<< "Введите начальный размер массива, конечный размер и шаг изменения размера массива\n";
			std::cin >> start >> stop >> step;
			std::cout << "Введите количество повторений сортировки: ";
			std::cin >> count;
			getTimeResults(start, stop, step, count);
		}
	}
	return 0;
}