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
    string sub();

    vector<int> v1;
    vector<int> v2;

   private:
    string toString(const vector<int>& v);
    bool isGreaterEqual();
    
    string subHelper(vector<int>& v1, vector<int>& v2);
};

#endif
