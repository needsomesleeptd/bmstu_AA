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
	std::size_t matrix_size = 0;
	std::vector<std::vector<float>> u, v;
	std::vector<std::vector<float>> matrix, s;
	std::cout << "Singular Value Decomposition (SVD):\n\n";

	std::cout << "Enter size of matrix N = (50x50 max): "; std::cin >> matrix_size;

	if (matrix_size <= 50)
	{
		generate_matrix(matrix, matrix_size, matrix_size);

		std::cout << "\nA = \n"; print_matrix(matrix);

		svd(matrix, s, u, v);

		std::cout << "\nS = \n"; print_matrix(s);
		std::cout << "\nU = \n"; print_matrix(u);
		std::cout << "\nV = \n"; print_matrix(v);
	}

	else std::cout << "Wrong matrix size... (matrix decomposition recommended)";

	std::cin.get();
	std::cin.get();

	return 0;
}