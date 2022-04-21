#ifndef SQ_HPP
#define SQ_HPP

#include <vector>
#include <iostream>
#include <string>
using namespace std;

vector<int> closestIndex(vector<int>& nums);
vector<int> maxSlidingWindow(vector<int>& nums, int k);
vector<int> kmp(string s, string pattern);
int strStr(string haystack, string needle);
string shortestPalindrome(string s);

#endif