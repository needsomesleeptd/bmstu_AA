#include <iostream>
#include <string>
#include <vector>

void printVector(const std::vector<int>& a)
{
	for (int i : a)
		std::cout << i << ' ';
}


int main() {

	srand(time(0));

	int elemCnt = 4;                                                   //(1)
	std::vector<int> arr(elemCnt);                                            //(2)

	for (int i = 0; i < elemCnt; ++i)
		arr[i] = rand() % 1000 - 500;

	std::cout << "Prev: ";
	printVector(arr);
	std::cout << std::endl;

	for (int step = 1; step < elemCnt; step = step * 2){            //(3)

		for (int l = 0; l < elemCnt - 1; l += 2 * step){   //(4)

			int m = std::min(l + step - 1, elemCnt - 1),            //(5)
			r = std::min(l + 2 * step - 1, elemCnt - 1);      //(6)

			int i = l,                                        //(7)
			j = m + 1,                                     //(8)
			pos = 0,                                         //(9)
			len = r - l + 1;                          //(10)

			std::vector<int> tmp(len);                       //(11)

			while (i <= m || j <= r) {                     //(12)

				if (i <= m && (j > r || arr[i] < arr[j])) {//(13)
					tmp[pos] = arr[i];                           //(14)
					i++;                                         //(15)
				}
				else {
					tmp[pos] = arr[j];                           //(16)
					j++;                                         //(17)
				}
				pos++;                                           //(18)
			}

			for (int k = 0; k < len; ++k)                        //(19)
				arr[k + l] = tmp[k];                          //(20)
		}
	}

	std::cout << "After: ";
	printVector(arr);
}
