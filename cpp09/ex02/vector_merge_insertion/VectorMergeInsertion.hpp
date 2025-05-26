#ifndef VECTOR_MERGE_INSERTION_HPP
# define VECTOR_MERGE_INSERTION_HPP

# include "../ISortStrategy.hpp"
# include "VectorChunk.hpp"

class VectorMergeInsertion : public ISortStrategy
{
    private:
        std::vector<int> vector;

        // void _make_pairs(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& chunks);
        // void _init_to_insert_and_main_chain(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain);
        // void _insert_to_main_chain(std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain);

        void _merge_insertion(std::vector<VectorChunk>& chunks, int depth);

    public:
        VectorMergeInsertion();
        VectorMergeInsertion(const VectorMergeInsertion& other);
        VectorMergeInsertion& operator=(const VectorMergeInsertion& other);
        ~VectorMergeInsertion();

        void             copy_numbers(const std::vector<int>& vec);
        std::vector<int> get_numbers() const;

        void sort();
};

#endif
