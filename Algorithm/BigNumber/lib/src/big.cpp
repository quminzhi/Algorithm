#include "big.hpp"

#include <sstream>

Big::Big(string s1, string s2) {
    for (auto it = s1.rbegin(); it != s1.rend(); it++) {
        v1.push_back(*it - '0');
    }
    for (auto it = s2.rbegin(); it != s2.rend(); it++) {
        v2.push_back(*it - '0');
    }
}

string Big::add() {
    // result must be at most max(v1.size, v2.size) + 1 bits
    vector<int> result(max(v1.size(), v2.size()) + 1, 0);
    int i = 0, j = 0, carry = 0;
    int k = 0;   // result
    int t = 0;
    while (i < v1.size() && j < v2.size()) {
        t = v1[i++] + v2[j++] + carry;
        result[k++] = t % 10;
        carry = t / 10;
    }
    while (i < result.size() && carry != 0) {
        t = v1[i++] + carry;
        result[k++] = t % 10;
        carry = t / 10;
    }
    while (j < result.size() && carry != 0) {
        t = v2[j++] + carry;
        result[k++] = t % 10;
        carry = t / 10;
    }

    // pop 0 on the most significant bit
    if (result[result.size() - 1] == 0) {
        result.pop_back();
    }

    return toString(result);
}

/**
 * @brief A - B:
 * if A >= B, calculate A - B
 * if A < B, calculate -(B - A)
 *
 * Assumed that each time we calculate Ai - Bi we have to borrow one from higher bit.
 * We use carry as well to compensate the borrow.
 *
 * ex> 9(Ai) - 5(Bi) = 9 + 10(borrow) - 5 = 14 ==> 4 and carry = 1
 * this carry will compensate the borrow and the effect is there is no borrow in last
 * calculation.
 *
 * @return string
 */
string Big::sub() {
    if (isGreaterEqual()) {
        return subHelper(v1, v2);
    } else {
        string absVal = subHelper(v2, v1);
        return absVal.insert(0, "-");   // add negative sign
    }
}

/**
 * @brief Assumed that v1 >= v2
 *
 * @param v1
 * @param v2
 * @return string
 */
string Big::subHelper(vector<int>& v1, vector<int>& v2) {
    vector<int> result(v1.size(), 0);
    int i = 0, j = 0, k = 0;
    int t = 0, borrow = 0, carry = 0;   // assumed borrow every time
    while (i < v1.size() && j < v2.size()) {
        t = v1[i++] + 10 - v2[j++] - borrow + carry;
        borrow = 1;
        carry = t / 10;
        result[k++] = t % 10;
    }
    // carry == 0 means borrowing 1 from higher bit exists
    while (i < v1.size() && carry == 0) {
        t = v1[i++] + 10 - borrow + carry;
        carry = t / 10;
        result[k++] = t % 10;
    }

    // pop consecutive 0 from the most significant bit
    i = result.size() - 1;
    for (; i >= 0; i--) {
        if (result[i] != 0) break;
    }
    if (i < result.size() - 1) {
        result.erase(result.begin() + i + 1, result.end());
    }

    return toString(result);
}

string Big::toString(const vector<int>& v) {
    ostringstream os;
    for (auto it = v.rbegin(); it != v.rend(); it++) {
        os << *it;
    }
    return os.str();
}

bool Big::isGreaterEqual() {
    if (v1.size() > v2.size()) {
        return true;
    }
    if (v1.size() < v2.size()) {
        return false;
    }
    if (v1.size() == v2.size()) {
        // from high to low bit
        for (int i = v1.size() - 1; i >= 0; i--) {
            if (v1[i] > v2[i]) {
                return true;
            }
            if (v1[i] < v2[i]) {
                return false;
            }
        }
    }
    // equal return true
    return true;
}