#include <iostream>
#include <string>
#include <locale>
#include <vector>

#include "measure.h"
#include "sorts.h"

int main()
{
	/*getTimeResults(100,
		10000000,
		10000,
		100,
		2,
		200);*/
	std::vector<int> test = { 3, -1, 2, 5};


	mergeSortMultiThread(test,0,test.size() - 1,3);
	printVector(test);
	//mergeSortMultiThread(test, 0, 1,23);-



}
