#include "houserobber.h"
#include <string>
#include <unordered_map>
#include "GUI/SimpleTest.h"

string vec2string(vector<int> vec) {
    string s;
    for (int& mem : vec) {
        s += mem;
    }
    return s;
}

int robHelper(vector<int>& money, vector<int>& houses, unordered_map<string, int> buffer) {
    if (houses.size() == 0) return 0;
    if (houses.size() == 1) return money[houses[0]];

    string bufferKey = vec2string(houses);
    if (buffer.find(bufferKey) != buffer.end()) {
        return buffer[bufferKey];
    }
    else {
        // TODO: backup for restore after backtracking
        int moneyFromHouse = money[0];
        int houseID = houses[0];
        int moneyOfNeighbor = money[1];
        int houseIDofNeighbor = houses[1];
        // TODO: choose
        // do not rob
        money.erase(money.begin()); // get rid of the first house
        houses.erase(houses.begin());
        int notRob = robHelper(money, houses, buffer);
        money.erase(money.begin()); // get rid of the neighbor of the first house
        // rob
        houses.erase(houses.begin());
        int justRob = robHelper(money, houses, buffer) + moneyFromHouse;
        // unchoose
        money.insert(money.begin(), moneyOfNeighbor);
        money.insert(money.begin(), moneyFromHouse);
        houses.insert(houses.begin(), houseIDofNeighbor);
        houses.insert(houses.begin(), houseID);

        // TODO: cache result
        string bufferKey = vec2string(houses);
        buffer[bufferKey] = max(notRob, justRob);
        return buffer[bufferKey];
    }
}

/*
 * Function: rob_sol1
 * ------------------------------------
 * As always, the problem is clearly a decision problem, which means it can be solved by
 * recursion (choose and not choose). But the problem here is time complexity of recursion
 * is O(N!) for this problem, which is undesirable.
 *
 * Assume that there are 5 houses on the street.
 * moneyInHouses = {4, 12, 6, 1, 5}
 *    HouseID    =  0  1   2  3  4
 *
 * Define f([...]) as the maximum money we will rob in houses [...].
 *
 * We, as a gang of robbers, are at the front door of the first house. If we rob this house?
 * if so, the maximum money we will get is f[{2, 3, 4}] + money[0]
 * otherwise, we will get f[{1, 2, 3, 4}]
 *
 * So we will get f[{0, 1, 2, 3, 4}] = max(f[{1, 2, 3, 4}], f[{2, 3, 4}] + money[0])
 *
 * To improve the algorithm, we are able to build a buffer to cache calculation.
 *
 * buffer[vector(houses)] = int(money);
 * A strategy to design buffer. If we have to let vector to be the key of hashmap? Of course
 * not. One way to mapping is use a string to concatenate every number, that will be unique.
 * buffer[string] = int(money)
 *
 * Base case:
 *      no house then return 0;
 *      only one house return money[houseID];
 * Recursion:
 *      f[houses to rob] = max(f[do not rob the first houses],
 *                             f[rob the first house] + money[first house])
 */
int rob_sol1(vector<int>& nums) {
    unordered_map<string, int> buffer;
    vector<int> houseID(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        houseID[i] = i;
    }
    int result = robHelper(nums, houseID, buffer);

    return result;
}

vector<int> subVector(vector<int>& nums, int begin, int end) {
    vector<int> sub;
    for (int i = begin; i < end; i++) {
        sub.push_back(nums[i]);
    }
    return sub;
}

/*
 * Function: rob_sol2
 * ------------------------------------
 * Now we are going to solve it with dynamic programming from bottom (simplest) to top
 * (hard).
 *
 * Initialization:
 * f[{}] = 0;
 * f[{houseID}] = houseVal;
 *
 * Derivation:
 * ===> f[{houseID1, houseID2}] = max {
 *          f[{houseID2}], f[{}] + f[{houseID1}]
 *      }
 *
 * What's the size of f? houses.size()!
 * What's the type of f? hashmap<string, int>
 */
int rob_sol2(vector<int>& nums) {
    unordered_map<string, int> f;
    string mapKey;
    f[mapKey] = 0;
    for (int i = 0; i < nums.size(); i++) {
        mapKey = vec2string({nums[i]});
        f[mapKey] = nums[i];
    }

    int begin = 0;
    int windowSize = 2;
    int end = begin + windowSize;
    while (windowSize <= nums.size()) {
        while (end <= nums.size()) {
            vector<int> subVec = subVector(nums, begin, end);
            string key = vec2string(subVec);
            // TODO: choose
            int potentialMoney = subVec[0];
            // not rob:
            subVec.erase(subVec.begin());
            int notRob = f[vec2string(subVec)];
            subVec.erase(subVec.begin()); // neighbor
            int justRob = f[vec2string(subVec)] + potentialMoney;
            f[key] = max(notRob, justRob);

            begin++;
            end++;
        }
        windowSize++;
        begin = 0;
        end = begin + windowSize;
    }

    return f[vec2string(nums)];
}


/*
 * Function: rob_sol3
 * ------------------------------------
 * A good abstraction of problem or say a good definition of f is such important!!!
 *
 * Can we make it easier? Do we have to record all solutions to every cases as last algorithm
 * does? Of course NOT.
 *
 * robFrom(i)= max(robFrom(i+1), robFrom(i+2) + nums(i));
 *
 * Notice: in the sol2, we have done a lot of unnecessary work, such as calculate f({2, 3, 4}) ...
 */
int rob_sol3(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int n = nums.size();
    vector<int> startFrom(n + 1, 0);
    startFrom[n] = 0;
    startFrom[n-1] = nums[n-1];
    for (int i = n-2; i >= 0; i--){
        startFrom[i] = max(startFrom[i+1], startFrom[i+2] + nums[i]);
    }

    return startFrom[0];
 }

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for rob_sol1():") {
    vector<int> nums1 = {1,2,3,1};
    EXPECT_EQUAL(rob_sol1(nums1), 4);

    vector<int> nums2 = {2,7,9,3,1};
    EXPECT_EQUAL(rob_sol1(nums2), 12);

//    // Time Limit Exceeded. Ops!
//    vector<int> nums3 = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
//    EXPECT_EQUAL(rob_sol1(nums3), 20);
}

PROVIDED_TEST("Test for rob_sol2():") {
    vector<int> nums1 = {1,2,3,1};
    EXPECT_EQUAL(rob_sol2(nums1), 4);

    vector<int> nums2 = {2,7,9,3,1};
    EXPECT_EQUAL(rob_sol2(nums2), 12);

//    // Time Limit Exceeded. Ops!
//    vector<int> nums3 = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
//    EXPECT_EQUAL(rob_sol1(nums3), 20);
}

PROVIDED_TEST("Test for rob():") {
    vector<int> nums1 = {1,2,3,1};
    EXPECT_EQUAL(rob_sol3(nums1), 4);

    vector<int> nums2 = {2,7,9,3,1};
    EXPECT_EQUAL(rob_sol3(nums2), 12);

    // Time Limit Exceeded. Ops!
    vector<int> nums3 = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
    EXPECT_EQUAL(rob_sol3(nums3), 3365);
}
