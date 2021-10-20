#ifndef BADVERSION_H
#define BADVERSION_H

#include <vector>
using namespace std;

/* Suppose you have n versions [1, 2, ..., n] and you want to find out the first
 * bad one, which causes all the following ones to be bad.
 *
 * ex> G G G B B B (1-based)  return: 4
 *     G G G G                return: -1
 */

bool isBadVersion(const vector<char>& versions, int n);
int firstBadVersion(int n);


#endif // BADVERSION_H
