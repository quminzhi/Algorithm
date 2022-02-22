#include "a.hpp"
#include <iostream>

void foo_a() {
    std::cout << "I'm an internal function foo_a()" << std::endl;
    std::cout << "And I am able to call external function foo_e()" << std::endl;
    foo_e();
}