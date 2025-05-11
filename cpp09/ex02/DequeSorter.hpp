#ifndef DEQUE_SORTER_HPP
# define DEQUE_SORTER_HPP

# include "Sorter.hpp"

class DequeSorter : public Sorter
{
    private:
        std::deque<int> deque;

    public:
        DequeSorter();
        DequeSorter(const DequeSorter& other);
        DequeSorter& operator=(const DequeSorter& other);
        ~DequeSorter();

        void read_inputs(const std::vector<int>& inputs);
        
        void merge_insertion_sort();
        void selection_sort();

        const std::deque<int>& get_deque() const;
};

std::ostream& operator<<(std::ostream& os, const std::deque<int>& d);

#endif
