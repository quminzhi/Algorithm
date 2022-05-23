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

class SegmentTree {
    public:
        SegmentTree(const vector<int>& arr) {
            int n = arr.size();
            build(1, 1, n);
            for (int i = 1; i <= n; i++) {
                modify(i, i, arr[i - 1]);   // arr is 0 based;
            }
        }

        /* build tree */
        void build(int u, int l, int r) {
            tr[u].l = l;
            tr[u].r = r;
            if (l == r) return;   // min segment
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
        };

        /* calculate parents property info from childrens's property info */
        void pushup(int u) {   // indexed by indices (int ~= Node*)
            tr[u].vMax = max(tr[u << 1].vMax, tr[u << 1 | 1].vMax);
        };

        void modify(int u, int vOld, int vNew) {
            // find leaf node of modified element
            if (tr[u].l == tr[u].r) tr[u].vMax = vNew;
            else {
                int mid = tr[u].l + tr[u].r >> 1;
                if (vOld <= mid) modify(u << 1, vOld, vNew);
                else modify(u << 1 | 1, vOld, vNew);
                // backtracking: update parent
                pushup(u);
            }
        };

        /* query property of segment [l, r] */
        int query(int u, int l, int r) {
            // case 1: include
            if (tr[u].l >= l && tr[u].r <= r) return tr[u].vMax;
            int mid = tr[u].l + tr[u].r >> 1;
            int winner;
            if (l <= mid) winner = query(u << 1, l, r);
            if (r > mid) winner = max(winner, query(u << 1 | 1, l, r));
            return winner; 
        };

    private:
        struct Node {
            int l, r;
            int vMax;
        } tr[100010];
};

#endif