#include <iostream>
#include "fact.hpp"
#include "a.hpp" // include external "e.hpp"
#include "b.hpp"
#include "c.hpp" // external
#include "d.hpp" // external
using namespace std;
    
int main(int argc, char* argv[]) {
    cout << "The factorial of 10 is " << fact(10) << endl;
    foo_a();
    foo_b();
    foo_c();
    foo_d();
    cout << "Main: hello world" << endl;

    return 0;
}