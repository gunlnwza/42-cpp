#ifndef VECTOR_MERGE_INSERTION
# define VECTOR_MERGE_INSERTION

# include "ISortStrategy.hpp"

class VectorMergeInsertion : public ISortStrategy
{
    private:
        std::vector<int> vector;

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
