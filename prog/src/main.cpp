#include <iostream>
#include "table.hpp"
int main()
{

	std::string st1 = "wwwwwwc";
	std::string st2 = "bbbbbbc";
	Matrix mat(st1.size(),st2.size());
	std::cout << "MatrixDist ==" << mat.findMatrixDistDamerau(st1, st2);
	std::cout << std::endl;
	mat.printMatrix();
	std::cout << std::endl;
	std::cout << "RecurseDistMemDamerau ==" << mat.findRecurseDistMemDamerau(st1, st2);
	std::cout << std::endl;
	std::cout << "RecurseDistDamerau ==" << mat.findRecurseDistDamerau(st1, st2);



	return 0;
}
