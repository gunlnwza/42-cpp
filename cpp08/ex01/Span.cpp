#include "Span.hpp"

Span::Span() : max_length(0)
{}

Span::Span(unsigned int N) : max_length(N)
{}

Span::Span(const Span& other) : max_length(other.max_length), vector(other.vector)
{}

Span& Span::operator=(const Span& other)
{
	if (this == &other)
		return (*this);

	this->max_length = other.max_length;
	this->vector = other.vector;
	return (*this);
}

Span::~Span(void)
{}


void	Span::addNumber(int num)
{
	if (this->vector.size() >= static_cast<unsigned long>(this->max_length))
		throw (std::out_of_range("Array is full, cannot add number"));

	this->vector.push_back(num);
}


int	Span::shortestSpan(void)
{
	if (this->vector.size() <= 1)
		throw (std::out_of_range("Too few numbers to find span"));

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

int	Span::longestSpan(void)
{
	if (this->vector.size() <= 1)
		throw (std::out_of_range("Too few numbers to find span"));

	std::vector<int> v(this->vector);
	std::sort(v.begin(), v.end());

	int	max_span = v.at(v.size() - 1) - v.at(0);
	return (max_span);
}
