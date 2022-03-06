#include "sorting.hpp"

void qsort(vector<int>& vec, int left, int right) {
    int i = left;
    int j = right;
    int chosen = left + ((right - left) >> 1);
    int pivot = vec[chosen];
    swap(vec[left], vec[chosen]);
    while (i < j) {
        while ((i < j) && (vec[j] >= pivot)) j--;
        vec[i] = vec[j];
        while ((i < j) && (vec[i] < pivot)) i++;
        vec[j] = vec[i];
    }
    vec[i] = pivot;

    if (left < i-1) qsort(vec, left, i-1);
    if (i+1 < right) qsort(vec, i+1, right);
}
