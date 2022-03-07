#include "shuffleanarray.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <testing/SimpleTest.h>

vector<int> ShuffleAnArray::reset() {
    for (int i = 0; i < nums.size(); i++) {
        nums[i] = origins[i];
    }

    return nums;
}

/**
 * @brief ShuffleAnArray::shuffle
 * @return
 * Select from choices randomly.
 */
vector<int> ShuffleAnArray::shuffle() {
//    srand(time(NULL));
    vector<int> choices = origins;
    int chosen;
    int size = choices.size();
    for (int i = 0; i < size; i++) {
        chosen = rand() % choices.size();
        nums[i] = choices[chosen];
        choices.erase(choices.begin() + chosen);
    }

    return nums;
}

/**
 * @brief ShuffleAnArray::shuffle2
 * @return
 * N time's random swap to simulate permutation.
 */
vector<int> ShuffleAnArray::shuffle2() {
//    srand(time(NULL));
    int chosen;
    for (int i = 0; i < nums.size(); i++) {
        chosen = rand() % nums.size();
        // swap nums[i] and nums[chosen]
        swap(nums[i], nums[chosen]);
    }

    return nums;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {1, 2, 3};
    ShuffleAnArray shuf(nums);
    shuf.shuffle();
    EXPECT(shuf.reset() == nums);
    shuf.shuffle();
    shuf.shuffle();
}
