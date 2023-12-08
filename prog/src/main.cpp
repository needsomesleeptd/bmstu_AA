#include <iostream>
#include <string>
#include "sorts.h"
#include <locale>
#include "measure.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Сортировка массива с использованием сортировки слиянием при 1 потоке\n"
                   "2)Сортировка массива с использованием сортировки слиянием при нескольких потоках\n"
                   "3)Расчет времени\n";

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
		if (1 <= request && request <= 2)
		{
			int n = -1;
			while (n <= 0)
			{
				std::cout << "Введите  размер массива для сортировки:\n";
				std::cin >> n;
				if (n <= 0)
					std::cout << "Введенная размерность массива невалидна\n";

			}
			std::cout << "Введите массив для сортировки:\n";
			std::vector<int> vec(n);
			for (int i = 0; i < n; i++)
			{
				std::cin >> vec[i];
			}
			int threadCnt = -1;
			if (request == 2)
			{
				while (threadCnt < 0)
				{
					std::cout << "Введите число дополнительных потоков для сортировки\n";
					std::cin >> threadCnt;
					if (threadCnt < 0)
						std::cout << "Введенное число дополнительных потоков невалидно\n";

				}
			}

			switch (request)
			{
			case 1:
				mergeSort(vec, 0, vec.size() - 1);
				break;
			case 2:

				mergeSortMultiThread(vec, 0, vec.size() - 1, threadCnt);
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
			int startThread, stopThread;
			std::cout
				<< "Введите начальный размер массива, конечный размер и шаг изменения размера массива\n";
			std::cin >> start >> stop >> step;
			std::cout << "Введите количество повторений сортировки: ";
			std::cin >> count;
			std::cout << "Введите начальное число потоков массива, конечное число потоков\n";
			std::cin >> startThread >> stopThread;
			getTimeResults(start, stop, step, count, startThread, stopThread);
		}
	}
	return 0;
}