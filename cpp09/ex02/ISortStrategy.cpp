#include "ISortStrategy.hpp"


ISortStrategy::ISortStrategy()
: name(""), compare_count(0)
{}

ISortStrategy::ISortStrategy(const ISortStrategy& other)
{
    *this = other;
}

ISortStrategy& ISortStrategy::operator=(const ISortStrategy& other)
{
    this->name = other.name;
    this->compare_count = other.compare_count;
    return (*this);
}

ISortStrategy::~ISortStrategy() {}


std::string ISortStrategy::get_name() const
{
    return (this->name);
}

int ISortStrategy::get_compare_count() const
{
    return (this->compare_count);
}
