#ifndef SQ_HPP
#define SQ_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> closestIndex(vector<int>& nums);
vector<int> maxSlidingWindow(vector<int>& nums, int k);
vector<int> kmp(string s, string pattern);

int strStr(string haystack, string needle);
string shortestPalindrome(string s);

#define N 100010

class Trie {
   private:
    int child[N][26];
    int v[N];
    int idx = 0;

   public:
    void insert(string str);
    int query(string str);
};

#endif