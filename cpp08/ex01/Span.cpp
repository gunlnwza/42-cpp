#include "Span.hpp"

Span::Span() : max_element_count(0)
{}

Span::Span(const Span& other)
: max_element_count(other.max_element_count), vector(other.vector)
{}

Span& Span::operator=(const Span& other)
{
    if (this == &other)
        return (*this);

    this->max_element_count = other.max_element_count;
    this->vector = other.vector;
    return (*this);
}

Span::~Span(void)
{}

Span::Span(unsigned int N)
: max_element_count(N)
{
    this->vector.reserve(N);
}


void Span::addNumber(int num)
{
    if (this->vector.size() >= static_cast<unsigned long>(this->max_element_count))
        throw (std::runtime_error("Span is full, cannot add number"));

    this->vector.push_back(num);
}

unsigned int Span::shortestSpan()
{
    if (this->vector.size() <= 1)
        throw (std::runtime_error("Too few numbers to find shortest span"));

    std::vector<int> v(this->vector);
    std::sort(v.begin(), v.end());
    
    int	min_span = v.at(1) - v.at(0);
    for (unsigned long i = 1; i < v.size() - 1; i++)
    {
        int	span = v.at(i + 1) - v.at(i);
        if (span < min_span)
            min_span = span;
    }
    return (min_span);
}

unsigned int Span::longestSpan()
{
    if (this->vector.size() <= 1)
        throw (std::runtime_error("Too few numbers to find longest span"));

    std::vector<int> v(this->vector);
    std::sort(v.begin(), v.end());

    int	max_span = v.at(v.size() - 1) - v.at(0);
    return (max_span);
}
