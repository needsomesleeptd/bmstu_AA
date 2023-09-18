#include <iostream>
#include <string>
#include "table.hpp"
#include <locale>
#include "timings.h"
int main()
{
	setlocale(LC_ALL, "");
	/*std::wstring st1 = L"ВФА";
	std::wstring st2 = L"АВФ";
	Matrix mat(st1.size(),st2.size());

	std::cout << "MatrixDist ==" << mat.findMatrixDistDamerau(st1, st2);
	std::cout << std::endl;
	mat.printMatrix();
	std::cout << std::endl;
	std::cout << "RecurseDistMemDamerau ==" << mat.findRecurseDistMemDamerau(st1, st2);
	std::cout << std::endl;
	std::cout << "RecurseDistDamerau ==" << mat.findRecurseDistDamerau(st1, st2);*/
	//getTimeResultsWord(10, 10);
	//std::wcin.imbue(std::locale(".OCP"));
	//std::wcout.imbue(std::locale(".OCP"));
	std::wstring menu = L"0.Выйти из меню\n"
						"1.Расчет расстояния Левенштейна с помощью матрицы\n"
						"2.Расчет расстояния Дамерау-Левенштейна с помощью матрицы\n"
						"3.Расчет расстояния Дамерау-Левенштейна с помощью рекурсии без мемоизации\n"
						"4.Расчет расстояния Дамерау-Левенштейна с помощью рекурсии с мемоизации\n"
						"5.Вывести временные замеры различных методов\n"
						"6.Сменить флаг вывода матриц\n"
						"7.Провести расчет всеми алгоритмами";

	int curCommand = 1;
	bool matrixShowFlag = false;
	while (curCommand != 0)
	{
		//std::cout <<"123";
		std::wcout << menu;
		std::wcout<< L"\nВведите номер требуемой комманды: \n";
		std::wcin >> curCommand;
		if (!curCommand)
			break;
		else  if (curCommand < 5 || curCommand == 7)
		{
			std::wstring st1;
			std::wstring st2;
			std::wcout << L"Введите первое слово: \n";
			std::wcin >> st1;
			std::wcout << L"Введите второе слово: \n";
			std::wcin >> st2;

			Matrix mat(st1.size(), st2.size());
			size_t distance = 0;
			if (curCommand == 1 || curCommand == 7)
			{
				distance = mat.findMatrixDistLev(st1, st2);
				if (matrixShowFlag)
				{
					std::wcout << L"\nПолученная матрица: \n";
					mat.printMatrix();
				}
				std::wcout << L"\nПолученное расстояние Левенштейна с помощью матрицы: \n";
				std::wcout << distance << L"\n";
			}
			if (curCommand == 2 || curCommand == 7)
			{
				distance = mat.findMatrixDistDamerau(st1, st2);
				if (matrixShowFlag)
				{
					std::wcout << L"\nПолученная матрица: \n";
					mat.printMatrix();
				}
				std::wcout << L"\nПолученное расстояние Дамерау-Левенштейна с помощью матрицы: \n";
				std::wcout << distance << L"\n";
			}
			if (curCommand == 3 || curCommand == 7)
			{
				distance = mat.findMatrixDistDamerau(st1, st2);
				std::wcout << L"\nПолученное расстояние Дамерау-Левенштейна с помощью рекурсии: \n";
				std::wcout << distance << L"\n";
			}
			if (curCommand == 4 || curCommand == 7)
			{
				distance = mat.findRecurseDistMemDamerau(st1, st2);
				std::wcout << L"\nПолученное расстояние Дамерау-Левенштейна с помощью рекурсии с мемоизацией: \n";
				std::wcout << distance << L"\n";
			}


		}
		else if (curCommand == 5)
		{
			std::wcout << L"Введите начальную длину слова, конечную длину слова, шаг соответственно с новой строки:" << L"\n";
			int sizeBegin = 0;
			int sizeEnd = 0;
			int step = 0;
			int countIter = 0;
			std::wcin >> sizeBegin >> sizeEnd >> step;
			std::wcout << L"Введите количество повторений для каждой строки: ";
			std::wcin >> countIter;
			getTimeResults(sizeBegin,sizeEnd,step,countIter);
		}
		else if (curCommand == 6)
		{
			matrixShowFlag = !matrixShowFlag;
			if (matrixShowFlag)
				std::wcout << L"\nМатрицы будут выведены при следующем запуске\n";
			else
				std::wcout << L"\nВывод матриц отключен\n";
		}

	}

	//getTimeResults(1,15,1,5);




	return 0;
}
