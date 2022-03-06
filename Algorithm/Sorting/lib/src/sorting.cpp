#include "sorting.hpp"
#include <iostream>

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

    if (left < i - 1) qsort(vec, left, i - 1);
    if (i + 1 < right) qsort(vec, i + 1, right);
}

void merge_sort(vector<int>& vec, vector<int>& tmp, int left, int right) {
    if (left >= right) return;
    int mid = left + ((right - left) >> 1);

    merge_sort(vec, tmp, left, mid);
    merge_sort(vec, tmp, mid + 1, right);

    // backtracking
    // k: index of tmp vector
    // i: index of left sorted vector
    // j: index of right sorted vector
    int k = 0, i = left, j = mid + 1;
    while ((i <= mid) && (j <= right)) {
        if (vec[i] < vec[j]) {
            tmp[k++] = vec[i++];
        } else {
            tmp[k++] = vec[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = vec[i++];
    }
    while (j <= right) {
        tmp[k++] = vec[j++];
    }

    // copy tmp[0, k-1] to vec[left, right], k = right - left + 1
    for (int i = left, j = 0; j < k; i++, j++) {
        vec[i] = tmp[j];
    }
}