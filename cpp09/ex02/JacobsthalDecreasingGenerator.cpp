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
