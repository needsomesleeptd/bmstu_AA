#include <iostream>
#include <string>
#include "find.hpp"
#include <locale>
#include "find.hpp"
#include "timings.h"
std::string menu = "Меню:\n"
                   "0)Выход\n"
                   "1)Сортировка массива с использованием сортировки перемешивания\n"
                   "2)Сортировка массива с использованием поразрядной сортировки\n"
                   "3)Сортировка массива с использованием блочной сортировки\n"
                   "4)Расчет времени\n";

void printVec(std::vector<int>& v)
{
	for (auto&& i : v)
		std::cout << i << " ";
	std::cout << std::endl;
}

void printVecD(std::vector<std::pair<int,int>>& v)
{
	for (auto&& i : v)
		std::cout << i.first <<" " << i.second <<  " ";
	std::cout << std::endl;
}


int main()
{
	/*std::vector<std::pair<int, int>> temp;
	std::vector<int> s = { 1, 5, 6, 7 };
	int x = 7;
	std::cout << binSearch(s, x, temp) << "\n";
	printVecD(temp);*/
	std::vector<std::vector<std::pair<int, int>>> resultBF;
	std::vector<std::vector<std::pair<int, int>>> resultF;
	int count = 512;
	getTimeResultsMatrix(count,1,resultBF,resultF);
	for (int i = 0 ; i < count; i++)
	{
		std:: cout << i << " " << resultBF[i].size() << std::endl;
	}

}