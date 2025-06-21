#include "JacobsthalDecreasingGenerator.hpp"


JacobsthalDecreasingGenerator::JacobsthalDecreasingGenerator()
: a(1), b(1), cur(1)
{}

JacobsthalDecreasingGenerator::JacobsthalDecreasingGenerator(const JacobsthalDecreasingGenerator& other)
{
    *this = other;
}

JacobsthalDecreasingGenerator& JacobsthalDecreasingGenerator::operator=(const JacobsthalDecreasingGenerator& other)
{
    this->a = other.a;
    this->b = other.b;
    this->cur = other.cur;
    return (*this);
}

JacobsthalDecreasingGenerator::~JacobsthalDecreasingGenerator() {}

// get the current Jacobsthal number, and prepare the next number
// J(1) = 1
// J(2) = 1
// J(n) = J(n - 1) + 2 * J(n - 2)
// "(1) (3) 2 (5) 4 (11) 10 9 8 7 6 (21) 20 19 ..."
int JacobsthalDecreasingGenerator::next()
{
    int result;
    int next_jacobsthal_number;

    result = cur;
    cur--;
    if (cur <= a)
    {
        next_jacobsthal_number = b + 2 * a;
        a = b;
        b = next_jacobsthal_number;
        cur = b;
    }
    return (result);
}
