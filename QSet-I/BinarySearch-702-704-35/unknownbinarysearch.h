#ifndef UNKNOWNBINARYSEARCH_H
#define UNKNOWNBINARYSEARCH_H

#include <vector>
using namespace std;

/* You have a sorted array of unique elements and an unknown size. You do
 * not have an access to the array but you can use the ArrayReader interface
 * to access it.
 *
 * You are also given an integer target. Return the index k of the hidden
 * array where secret[k] == target or return -1 otherwise.
 */

class ArrayReader {
public:
    ArrayReader(const vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            this->secret.push_back(nums[i]);
        }
    }

    int get(int index) const {
        // how to use this feature?
        if ((index < 0) || (index >= secret.size())) {
            return INT_MAX;
        }
        else {
            return secret[index];
        }
    }

private:
    /* Constrains:
     * 1 <= secret.length <= 10^4
     * -10^4 <= secret[i], target <= 10^4
     */
    vector<int> secret;
};

int search_sol1(const ArrayReader& reader, int target);
int search_sol2(const ArrayReader& reader, int target);
int search_sol3(const ArrayReader& reader, int target); // more aggressive one


#endif // UNKNOWNBINARYSEARCH_H
