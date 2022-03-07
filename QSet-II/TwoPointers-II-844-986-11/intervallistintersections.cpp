#include "intervallistintersections.h"
#include "testing/SimpleTest.h"
#include <unordered_map>

/**
 * @brief intervalIntersection_sol1
 * @param firstList
 * @param secondList
 * @return
 * An example of closed interval intersections is as follows,
 *
 * ex>    list A:  -----    ---------  --------      --------
 *        list B: ---      ----- --------- ---- ---  ----
 *
 * Intersections:  --       ---- ----  --- ----      ----
 *
 * Intersection[i] == 1 means, [i, i+1) has been covered.
 * Use an unordered map to store overlappint points.
 *
 * The first idea is to simulate intersections with an array. Project A and B to
 * new list. The elements with value 2 consist of intersection list.
 */
vector< vector<int> > intervalIntersection_sol1(vector< vector<int> >& firstList, vector< vector<int> >& secondList) {
    int max_size = 1002;
    unordered_map<int, int> points;
    vector<int> intersection(max_size);
    vector< vector<int> > result;
    for (int i = 0; i < firstList.size(); i++) {
        if (points.find(firstList[i][0]) == points.end()) {
            points[firstList[i][0]] = 1;
        }
        else {
            points[firstList[i][0]]++;
        }
        if (points.find(firstList[i][1]) == points.end()) {
            points[firstList[i][1]] = 1;
        }
        else {
            points[firstList[i][1]]++;
        }
        for (int j = firstList[i][0]; j < firstList[i][1]; j++) {
            intersection[j]++;
        }
    }
    for (int i = 0; i < secondList.size(); i++) {
        if (points.find(secondList[i][0]) == points.end()) {
            points[secondList[i][0]] = 1;
        }
        else {
            points[secondList[i][0]]++;
        }
        if (points.find(secondList[i][1]) == points.end()) {
            points[secondList[i][1]] = 1;
        }
        else {
            points[secondList[i][1]]++;
        }
        for (int j = secondList[i][0]; j < secondList[i][1]; j++) {
            intersection[j]++;
        }
    }

    // TODO: push overlap points into result
    for (auto pair : points) {
        if (pair.second >= 2) {
            result.push_back({pair.first, pair.first});
        }
    }

    // TODO: construct output with two pointers, interval [l, r)
    int l = 0;
    int r = 0;
    int length = max(firstList[firstList.size()-1][1], secondList[secondList.size()-1][1]);
    while (l <= length) {
        // TODO: move l to the next 2
        while ((intersection[l] != 2) && (l < length)) {
            l++;
        }
        r = l;
        // TODO: r explore the end of consecutive 2
        while ((intersection[r] == 2) && (r < length)) {
            r++;
        }
        if (l < length) {
            result.push_back({l, r});
        }
        else {
            break;
        }
        l = r;
    }

    return result;
}

/**
 * Solution2 comes from the observation of the link between intersections and
 * A or B.
 *
 * Define: interval [a, b], b as endpoint of an interval
 *
 * ex>    list A:  -----    ---------  --------      --------
 *        list B: ---      ----- --------- ---- ---  ----
 *                  ^
 *  intersection:  -- ,which is [max(A[0][0], B[0][0]), min(A[0][1], B[0][1])]
 *                  ^
 *
 * Two observations are:
 * 1. the interval with smallest endpoint will intersect with only one interval in
 * the other list.
 * 2. the interval with smallest endpoint will share the same endpoint with
 * intersection interval.
 */
vector< vector<int> > intervalIntersection_sol2(vector< vector<int> >& firstList, vector< vector<int> >& secondList) {
    vector< vector<int> > result;
    int pa = 0;
    int pb = 0;
    while ((pa < firstList.size()) && (pb < secondList.size())) {
        // TODO: find interval with smallest endpoint
        int l = max(firstList[pa][0], secondList[pb][0]);
        int r = min(firstList[pa][1], secondList[pb][1]);
        if (l <= r) {
            result.push_back({l, r});
        }
        (firstList[pa][1] < secondList[pb][1]) ? pa++ : pb++;
    }

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector< vector<int> > firstList = {{0,2},{5,10},{13,23},{24,25}};
    vector< vector<int> > secondList = {{1,5},{8,12},{15,24},{25,26}};
    vector< vector<int> > result = intervalIntersection_sol1(firstList, secondList);
    EXPECT_EQUAL(result[0][0], 25);
    EXPECT_EQUAL(result[0][1], 25);
    EXPECT_EQUAL(result[4][0], 8);
    EXPECT_EQUAL(result[4][1], 10);
    EXPECT_EQUAL(result[5][0], 15);
    EXPECT_EQUAL(result[5][1], 23);
}

PROVIDED_TEST("Test for sol2:") {
    vector< vector<int> > firstList = {{0,2},{5,10},{13,23},{24,25}};
    vector< vector<int> > secondList = {{1,5},{8,12},{15,24},{25,26}};
    vector< vector<int> > result = intervalIntersection_sol2(firstList, secondList);
    EXPECT_EQUAL(result[0][0], 1);
    EXPECT_EQUAL(result[0][1], 2);
    EXPECT_EQUAL(result[4][0], 24);
    EXPECT_EQUAL(result[4][1], 24);
    EXPECT_EQUAL(result[5][0], 25);
    EXPECT_EQUAL(result[5][1], 25);
}
