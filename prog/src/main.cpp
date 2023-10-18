#include <iostream>
#include <string>
#include "table.hpp"
#include <locale>

std::string menu = "Menu:\n"
                   "0)Exit\n"
                   "1)Standard matrix multiplication\n"
                   "2)Vinograd matrix multiplication\n"
                   "3)Strassen matrix multiplication\n"
                   "4)Time mesaure\n"
                   "5)Memory measure";

int main()
{
	int request = -1;
	while (request != 0)
	{
		std::cout << menu << "\n";
		std::cout << "Enter your choice: ";
		std::cin >> request;
		std::cout << "\n";
		if (1 <= request && request <= 3)
		{
			int n1 = -1;
			int m1 = -1;
			while (n1 <= 0 || m1 <= 0)
			{
				std::cout << "Enter matrix1 dimensions(n and m):";
				std::cin >> n1 >> m1;
				if (n1 <= 0 || m1 <= 0)
					std::cout << "Matrix dimensions are invalid retry again\n";
			}
			Matrix mat1 = Matrix(n1, m1);
			std::cout << "Enter matrix1\n";
			mat1.scanMatrix();

			int n2 = -1;
			int m2 = -1;
			while (n2 <= 0 || m2 <= 0)
			{
				std::cout << "Enter matrix2 dimensions(n and m):";
				std::cin >> n2 >> m2;
				if (n2 <= 0 || m2 <= 0)
					std::cout << "Matrix dimensions are invalid, retry again\n";
			}
			Matrix mat2 = Matrix(n2, m2);
			std::cout << "Enter matrix2\n";
			mat2.scanMatrix();

			std::cout << "Matrix1 entered:\n";
			mat1.printMatrix();
			std::cout << "Matrix2 entered:\n";
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
				std::cout << "Matrix dimensions make them impossible to multiply\n";
			else
			{
				std::cout << "Result matrix:\n";
				res_matr.printMatrix();
			}

		}
	}
	return 0;
}