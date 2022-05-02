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

const int N = 100010;

class Trie {
   private:
    int child[N][26];
    int v[N];
    int idx = 0;

   public:
    void insert(string str);
    int query(string str);
};

class DisjointSet {
   private:
    int p[N];

   public:
    DisjointSet(int n);
    int find(int x);   // return set label of val x
    void merge(int x, int y);
};

#endif