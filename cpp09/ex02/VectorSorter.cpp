#include "VectorSorter.hpp"


VectorSorter::VectorSorter()
{}

VectorSorter::VectorSorter(const VectorSorter& other)
{
    *this = other;
}

VectorSorter& VectorSorter::operator=(const VectorSorter& other)
{
    this->vector = other.vector; return (*this);
}

VectorSorter::~VectorSorter()
{}


void VectorSorter::read_inputs(const std::vector<int>& inputs)
{
    this->vector = inputs;
}


void VectorSorter::sort()
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < vector.size(); j++)
        {
            compare_count++;
            if (vector[j] < vector[min_index])
                min_index = j;
        }
        if (min_index != i)
            std::swap(vector[i], vector[min_index]);
    }
}


const std::vector<int>& VectorSorter::get_vector() const
{
    return (this->vector);
}


std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
    size_t n;

    n = MAX_NUM_TO_SHOW;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
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
