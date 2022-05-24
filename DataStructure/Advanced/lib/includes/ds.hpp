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
    /* for arr with size of n, we need at least 4n memory space to save segment tree */
    SegmentTree(const vector<int>& arr) {
        int n = arr.size();
        build(1, 1, n);   // 1-based
        for (int i = 1; i <= n; i++) {
            modify(1, i, arr[i - 1]);   // arr is 0 based;
        }
    }

    /* build tree: interval division */
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

    void modify(int u, int idx, int vNew) {
        // find leaf node of modified element
        if (tr[u].l == idx && tr[u].r == idx)
            tr[u].vMax = vNew;
        else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (idx <= mid)
                modify(u << 1, idx, vNew);
            else
                modify(u << 1 | 1, idx, vNew);
            // backtracking: update parent
            pushup(u);
        }
    };

    /* query property of segment [l, r] */
    int query(int u, int l, int r) {
        // case 1: include
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].vMax;
        int mid = tr[u].l + tr[u].r >> 1;
        int winner = -inf;
        if (l <= mid) winner = max(winner, query(u << 1, l, r));
        if (r > mid) winner = max(winner, query(u << 1 | 1, l, r));
        return winner;
    };

   private:
    const int inf = 1e9;

    struct Node {
        int l, r;
        int vMax;
    } tr[1000];
};

class MaxSubarray {
   private:
    struct Node {
        int l, r;
        int prefix, postfix, sum, vMax;
    };

   public:
    MaxSubarray(vector<int> v) {
        const int n = v.size();
        build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            modify(1, i, v[i - 1]);
        }
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) return;
        int mid = tr[u].l + tr[u].r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    /* update regulation */
    void pushup(struct Node& p, struct Node& left, struct Node& right) {
        p.sum = left.sum + right.sum;
        p.prefix = max(left.prefix, left.sum + right.prefix);
        p.postfix = max(right.postfix, right.sum + left.postfix);
        // three possibles
        p.vMax = max(left.vMax, right.vMax);                 // left or right
        p.vMax = max(p.vMax, left.postfix + right.prefix);   // or combination of postfix and prefix
    }

    void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

    void modify(int u, int idx, int val) {
        if (tr[u].l == tr[u].r && tr[u].l == idx) {
            tr[u].postfix = tr[u].prefix = tr[u].sum = tr[u].vMax = val;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (idx <= mid)
                modify(u << 1, idx, val);
            else
                modify(u << 1 | 1, idx, val);
            pushup(u);
        }
    }

    // return the segment including ans
    Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        // only left
        if (r <= mid) return query(u << 1, l, r);
        // only right
        if (l > mid) return query(u << 1 | 1, l, r);
        // include left and right: three cases solved with pushup
        struct Node left = query(u << 1, l, r);
        struct Node right = query(u << 1 | 1, l, r);
        struct Node res;
        pushup(res, left, right);   // update res with left and right answer
        return res;
    }

   private:
    struct Node tr[1010];
};

/*
    1. one property: gcd(a1, a2, ..., an) = gcd(a1 - 0, a2 - a1, ..., an - an-1)
    i.e. gcd of original sequence is gcd of difference sequence

    2. maintain elements in segment tree in the form of difference sequence.
        - modify(u, l, r, add) -> modify(u, l, add) and modify(u, r + 1, -add) if r + 1 <= n
        - query(u, l, r) -> gcd(a[l], diff[l+1], ..., diff[r]) == gcd(a[l], gcd(diff[l+1], ..., diff[r]))
        where, a[l] = prefixSum[l + 1]
 */
class GCDTree {
   private:
    struct Node {
        int l, r;
        int sum, divisor;
    };

   public:
    GCDTree(const vector<int>& v) {
        n = v.size();
        // 0-based to 1-based
        vector<int> vv(v.begin(), v.end());
        vv.insert(vv.begin(), 0);
        build(vv, 1, 1, n);
    }

    void pushup(struct Node& p, struct Node& left, struct Node& right) {
        p.sum = left.sum + right.sum;
        p.divisor = gcd(left.divisor, right.divisor);
    }

    void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

    // segment: diff sequence
    void build(const vector<int>& v, int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            // leaf
            int diff = v[l] - v[l - 1];
            tr[u].divisor = diff;
            tr[u].sum = diff;
        } else {
            int mid = l + r >> 1;
            build(v, u << 1, l, mid);
            build(v, u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    // modify: change of value (DELTA) on [idx, idx], not replace with 'add'
    void modify(int u, int idx, int add) {
        if (tr[u].l == tr[u].r && tr[u].l == idx) {
            int t = tr[u].divisor + add;
            tr[u].divisor = tr[u].sum = t;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (idx <= mid)
                modify(u << 1, idx, add);
            else
                modify(u << 1 | 1, idx, add);
            pushup(u);
        }
    }

    // range modify
    void modify(int u, int l, int r, int add) {
        // update diff sequence
        modify(u, l, add);
        if (r + 1 <= n) modify(u, r + 1, -add);
    }

    struct Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) {
            // ans in left segment (known)
            return query(u << 1, l, r);
        } else if (l > mid) {
            // ans in right segment (known)
            return query(u << 1 | 1, l, r);
        } else {
            // ans need to be calculated by pushup
            struct Node left = query(u << 1, l, r);
            struct Node right = query(u << 1 | 1, l, r);
            struct Node res;
            pushup(res, left, right);
            return res;
        }
    }

    // decorator:
    // gcd(a[l], gcd(diff[l+1], ..., diff[r]))
    int query(int l, int r) {
        auto left = query(1, 1, l);   // for a[l]
        if (l + 1 > r) return left.sum;   // no diff sequence after a[l]
        auto right = query(1, l + 1, r); // gcd of diff[l+1 ... r]
        return abs(gcd(left.sum, right.divisor));
    }

   private:
    struct Node tr[1010];   // 4 * n
    int n;

    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }
};

#endif