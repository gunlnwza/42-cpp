#include "JacobsthalDecreasingGenerator.hpp"

JacobsthalDecreasingGenerator::JacobsthalDecreasingGenerator() : a(0), b(1), cur(1) {}
JacobsthalDecreasingGenerator::~JacobsthalDecreasingGenerator() {}

int JacobsthalDecreasingGenerator::next() {
    int res;
    int temp;

    if (a < cur && cur <= b)
    {
        res = cur;
        cur--;
    }
    else
    {
        temp = b + 2 * a;
        a = b;
        b = temp;
        cur = b;
        res = b;
    }
    return (res);
}
