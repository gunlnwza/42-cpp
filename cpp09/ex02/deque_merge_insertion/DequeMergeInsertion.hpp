#ifndef DEQUE_MERGE_INSERTION_HPP
# define DEQUE_MERGE_INSERTION_HPP

# include "../ISortStrategy.hpp"
# include "../JacobsthalDecreasingGenerator.hpp"
# include "DequeChunk.hpp"

class DequeMergeInsertion : public ISortStrategy
{
    private:
        std::deque<int> deque;

        void _make_pairs(std::deque<DequeChunk*>& chunks, std::deque<DequeChunk*>& pairs, DequeChunk** chunk);
        void _divide_pairs(std::deque<DequeChunk*>& pairs, DequeChunk* chunk, std::deque<DequeChunk*>& to_insert, std::deque<DequeChunk*>& main_chain);
        void _insert_to_main_chain(std::deque<DequeChunk*>& to_insert, std::deque<DequeChunk*>& main_chain);

        void _merge_insertion(std::deque<DequeChunk*>& chunks);

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
