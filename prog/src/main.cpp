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


	int n1 = -1;
	int m1 = -1;
	while (n1 <= 0 || m1 <= 0)
	{
		std::cout << "Введите n и m (высоту и ширину матрицы) ";
		std::cin >> n1 >> m1;
		if (n1 <= 0 || m1 <= 0)
			std::cout << "Введенные параметры матрицы не валидны: \n";
	}
	std::vector<std::vector<float>> mat(n1, std::vector<float>(m1));

	std::vector<std::vector<float>> u, v, s;
	svd(mat, s, u, v);

	std::cout << "\nS = \n";
	print_matrix(s);
	std::cout << "\nU = \n";
	print_matrix(u);
	std::cout << "\nV = \n";
	print_matrix(v);

	return 0;
}