#ifndef DEQUE_MERGE_INSERTION
# define DEQUE_MERGE_INSERTION

# include <deque>

# include "ISortStrategy.hpp"

class DequeMergeInsertion : public ISortStrategy
{
    private:
        std::deque<int> deque;

    public:
        DequeMergeInsertion();
        DequeMergeInsertion(const DequeMergeInsertion& other);
        DequeMergeInsertion& operator=(const DequeMergeInsertion& other);
        ~DequeMergeInsertion();

        void             copy_numbers(const std::vector<int>& inputs);
        std::vector<int> get_numbers() const;

        void sort();
};

#endif
