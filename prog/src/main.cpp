#include <iostream>
#include <string>
#include "timings.h"
#include "table.hpp"

std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Умножение матриц стандартным методом\n"
                   "2)Умножение алгоритмом Винограда\n"
                   "3)Умножение оптимизированным алгоритмом Винограда\n"
                   "4)Умножение алгоритмом Штрассена\n"
                   "5)Провести замеры по времени\n";


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
		if (1 <= request && request <= 4)
		{
			int n1 = -1;
			int m1 = -1;
			while (n1 <= 0 || m1 <= 0)
			{
				std::cout << "Введите n и m (высоту и ширину первой матрицы) ";
				std::cin >> n1 >> m1;
				if (n1 <= 0 || m1 <= 0)
					std::cout << "Введенные параметры матрицы не валидны\n";
			}
			Matrix mat1 = Matrix(n1, m1);
			std::cout << "Введите первую матрицу\n";
			mat1.scanMatrix();

			int n2 = -1;
			int m2 = -1;
			while (n2 <= 0 || m2 <= 0)
			{
				std::cout << "Введите n и m (высоту и ширину второй матрицы) ";
				std::cin >> n2 >> m2;
				if (n2 <= 0 || m2 <= 0)
					std::cout << "Введенные параметры матрицы не валидны\n";
			}
			Matrix mat2 = Matrix(n2, m2);
			std::cout << "Введите вторую матрицу\n";
			mat2.scanMatrix();

			std::cout << "Введенная первая матрица:\n";
			mat1.printMatrix();
			std::cout << "Введенная вторая матрица:\n";
			mat2.printMatrix();
			Matrix res_matr(0, 0);
			switch (request)
			{
			case 1:
				res_matr = mat1.dot(mat2);
			case 2:
				res_matr = mat1.dot_vin(mat2);
			case 3:
				res_matr = mat1.dot_vin_opt(mat2);
			case 4:
				res_matr = mat1.dot_shtrassen(mat2);
			}
			if (res_matr._n == 0 || res_matr._m == 0)
				std::cout << "Матрицы с данными параметрами невозможно умножить\n";
			else
			{
				std::cout << "Результирующая матрица:\n";
				res_matr.printMatrix();
			}

		}
		else
		{
			int start, stop, step;
			int count;
			std::cout
				<< "Введите начальную размерность квадратных матриц, конечную размерность и шаг изменения размерности матриц\n";
			std::cin >> start >> stop >> step;
			std::cout << "Введите количество повторений расчета произведений матриц каждой размерности\n";
			std::cin >> count;
			getTimeResults(start,stop,step,count);
		}
	}
	return 0;
}