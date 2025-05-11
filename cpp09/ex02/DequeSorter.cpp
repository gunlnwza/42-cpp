#include "DequeSorter.hpp"


DequeSorter::DequeSorter()
{}

DequeSorter::DequeSorter(const DequeSorter& other)
{
    *this = other;
}

DequeSorter& DequeSorter::operator=(const DequeSorter& other)
{
    this->deque = other.deque;
    return (*this);
}

DequeSorter::~DequeSorter()
{}


void DequeSorter::read_inputs(const std::vector<int>& inputs)
{
    for (std::vector<int>::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
        this->deque.push_back(*it);
}


void DequeSorter::sort()
{
    for (size_t i = 0; i < deque.size(); i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < deque.size(); j++)
        {
            compare_count++;
            if (deque[j] < deque[min_index])
                min_index = j;
        }
        if (min_index != i)
            std::swap(deque[i], deque[min_index]);
    }
}


const std::deque<int>& DequeSorter::get_deque() const
{
    return (this->deque);
}


std::ostream& operator<<(std::ostream& os, const std::deque<int>& d)
{
    size_t n;

    n = MAX_NUM_TO_SHOW;
    for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
    {
        if (n == 0)
        {
            std::cout << "[...]";
            break ;
        }
        std::cout << *it << " ";
        n--;
    }
    return (os);
}
