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
						"5.Вывести временные замеры различных методов";
	int curCommand = 1;
	while (curCommand != 0)
	{
		//std::cout <<"123";
		std::wcout << menu;
		std::wcout<< L"\nВведите номер требуемой комманды: \n";
		std::wcin >> curCommand;
		if (!curCommand)
			break;
		else  if (curCommand < 5)
		{
			std::wstring st1;
			std::wstring st2;
			std::wcout << L"Введите первое слово: \n";
			std::wcin >> st1;
			std::wcout << L"Введите второе слово: \n";
			std::wcin >> st2;
			std::wcout << L"Полученное расстояние: ";
			Matrix mat(st1.size(), st2.size());
			size_t distance = 0;
			if (curCommand == 1)
				distance = mat.findMatrixDistLev(st1,st2);
			else if (curCommand == 2)
				distance = mat.findMatrixDistDamerau(st1,st2);
			else if (curCommand == 3)
				distance = mat.findMatrixDistDamerau(st1,st2);
			else if (curCommand == 4)
				distance = mat.findRecurseDistMemDamerau(st1,st2);
			std::wcout << distance << L"\n";

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
	}

	//getTimeResults(1,15,1,5);




	return 0;
}
