#ifndef SORTING_HPP
#define SORTING_HPP

// write your library here
#include <vector>
using namespace std;

void qsort(vector<int>& vec, int left, int right);
void merge_sort(vector<int>& vec, vector<int>& tmp, int left, int right);

#endif
