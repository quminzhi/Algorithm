#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
using namespace std;

/**
 * Given a triangle array, return the minimum path sum from top to bottom.
 *
 * For each step, you may move to an adjacent number of the row below. More formally,
 * if you are on index i on the current row, you may move to either index i or index
 * i + 1 on the next row.
 */

int minimumTotal(vector< vector<int> >& triangle);

#endif // TRIANGLE_H
