//
// Created by Андрей on 10/09/2023.
//

#ifndef LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_
#define LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_

#include <queue>


void getTimeResultsWord(size_t wordsLen,int countProcessed);
void getTimeResults(int arrayStart, int arrayEnd, int arrayStep, int reqStart, int reqEnd, int reqStep);
void getMemResults(size_t wordLenStart,size_t wordLenStop,size_t wordLenStep,int countProcessed);
std::vector<int> generateVector(const size_t len);



#endif //LAB_01_AA_BMSTU_AA_PROG_SRC_TIMINGS_H_
