#include "VectorMergeInsertion.hpp"

#include <iostream>


VectorMergeInsertion::VectorMergeInsertion()
{
    this->name = "std::vector";
}

VectorMergeInsertion::VectorMergeInsertion(const VectorMergeInsertion& other)
{
    *this = other;
}

VectorMergeInsertion& VectorMergeInsertion::operator=(const VectorMergeInsertion& other)
{
    this->vector = other.vector;
    return (*this);
}

VectorMergeInsertion::~VectorMergeInsertion()
{}


void VectorMergeInsertion::copy_numbers(const std::vector<int>& inputs)
{
    // std::cout << "copy vector" << std::endl;
    this->vector = inputs;
}

std::vector<int> VectorMergeInsertion::get_numbers() const
{
    return (this->vector);
}


void VectorMergeInsertion::sort()
{
    // std::cout << "sort" << std::endl;
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
