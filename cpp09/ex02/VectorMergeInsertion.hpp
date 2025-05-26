#ifndef VECTOR_MERGE_INSERTION_HPP
# define VECTOR_MERGE_INSERTION_HPP

# include "ISortStrategy.hpp"
# include "VectorChunk.hpp"

class VectorMergeInsertion : public ISortStrategy
{
    private:
        std::vector<int> vector;

        void _merge_insertion(std::vector<VectorChunk>& chunks);

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
