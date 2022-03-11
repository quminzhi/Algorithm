#ifndef BIG_HPP
#define BIG_HPP

#include <string>
#include <vector>
using namespace std;

// write your library here
class Big {
   public:
    Big(string _s1, string _s2);

    string add();
    string add(vector<int>& v1, vector<int>& v2);
    string sub();
    string sub(vector<int>& v1, vector<int>& v2);
    string mul();
    string mul(vector<int>& v1, vector<int>& v2);

    vector<int> v1;
    vector<int> v2;

   private:
    string toString(const vector<int>& v);
    bool isGreaterEqual();

    vector<int> addHelper(vector<int>& v1, vector<int>& v2);
    string subHelper(vector<int>& v1, vector<int>& v2);
    string mulHelper(vector<int>& v1, vector<int>& v2);
    vector<int> mulDigit(vector<int>& v, int n);
};

#endif
