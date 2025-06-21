#include "DequeMergeInsertion.hpp"


DequeMergeInsertion::DequeMergeInsertion()
{
    this->name = "std::deque";
}

DequeMergeInsertion::DequeMergeInsertion(const DequeMergeInsertion& other)
: ISortStrategy(other)
{
    *this = other;
}

DequeMergeInsertion& DequeMergeInsertion::operator=(const DequeMergeInsertion& other)
{
    this->deque = other.deque;
    return (*this);
}

DequeMergeInsertion::~DequeMergeInsertion()
{}


void DequeMergeInsertion::copy_numbers(const std::vector<int>& inputs)
{
    this->deque.assign(inputs.begin(), inputs.end());
}

std::vector<int> DequeMergeInsertion::get_numbers() const
{
    std::vector<int> vec;

    vec.assign(this->deque.begin(), this->deque.end());
    return (vec);
}


void DequeMergeInsertion::sort()
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
