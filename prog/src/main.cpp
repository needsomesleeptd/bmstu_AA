#include <iostream>
#include "table.hpp"
#include <locale>
#include "timings.h"
int main()
{
	/*setlocale(LC_ALL, "Russian");
	std::wstring st1 = L"ВФА";
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
	getTimeResults(1,15,1,5);




	return 0;
}
