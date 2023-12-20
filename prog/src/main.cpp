#include <iostream>
#include <string>
#include "find.hpp"
#include <locale>
#include "find.hpp"
#include "timings.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Поиск элемента с помощью бинарного поиска\n"
                   "2)Поиск элемента с помощью линейного поиска\n"
                   "3)Расчет числа сравнений\n";

void printVec(std::vector<int>& v)
{
	for (auto&& i : v)
		std::cout << i << " ";
	std::cout << std::endl;
}

void printVecD(std::vector<std::pair<int, int>>& v)
{
	for (auto&& i : v)
		std::cout << i.first << " " << i.second << " ";
	std::cout << std::endl;
}

int main()
{
	/*
	std::vector<std::vector<std::pair<int, int>>> resultBF;
	std::vector<std::vector<std::pair<int, int>>> resultF;
	int count = 512;
	getTimeResultsMatrix(count, 1, resultBF, resultF);
	for (int i = 0; i < resultBF.size(); i++)
	{
		std::cout << i - 1 << " " << resultBF[i].size() << std::endl;
	}*/

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
				std::cout << "Введите  размер массива для поиска значения:\n";
				std::cin >> n;
				if (n <= 0)
					std::cout << "Введенная размерность массива невалидна\n";

			}
			std::cout << "Введите массив для поиска значения:\n";
			std::vector<int> vec(n);
			for (int i = 0; i < n; i++)
			{
				std::cin >> vec[i];
			}
			std::cout << "Введите значение для поиска:\n";
			int t;
			std::cin >> t;


			int res = 0;
			std::vector<std::pair<int,int>> resIndexes;
			switch (request)
			{
			case 1:
				res = search(vec,t,resIndexes);
				break;
			case 2:
				res = binSearch(vec,t,resIndexes);
				break;
			}
			if (res == -1)
				std:: cout << "Искомое значение не найдено\n";
			else
				std:: cout << "Индекс искомого значения:" << res << std::endl;
		}
		else
		{
			std::vector<std::vector<std::pair<int, int>>> resultBF;
			std::vector<std::vector<std::pair<int, int>>> resultF;
			std:: cout<< "Введите размер массива для поиска элементов: ";
			int n;
			std::cin >> n;
			getTimeResultsMatrix(n,1,resultBF,resultF);
			std::cout<< "| Ind | Bin | Lin |" << std::endl;
			for (int i = 0 ; i < resultF.size(); i++)
			{
				//if (i % 15 == 0)
					std::cout <<" | " << i - 1 << " | " << resultBF[i].size() << " | " << resultF[i].size() << "|" <<  std::endl;
			}

		}
	}
	return 0;

}