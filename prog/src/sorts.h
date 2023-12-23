//
// Created by Андрей on 10/09/2023.
//

#ifndef LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_1
#define LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_1
#include <vector>

void printVector(const std::vector<int>& a);
void mergeSort(std::vector<int> & arr, int left, int right);
void mergeSortMultiThread(std::vector<int>& nums, int s, int e, int availThreads);

#endif //LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_1