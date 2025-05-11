#ifndef VECTOR_SORTER_HPP
# define VECTOR_SORTER_HPP

# include "Sorter.hpp"

class VectorSorter : public Sorter
{
    private:
        std::vector<int> vector;

    public:
        VectorSorter();
        VectorSorter(const VectorSorter& other);
        VectorSorter& operator=(const VectorSorter& other);
        ~VectorSorter();

        void read_inputs(const std::vector<int>& inputs);
        
        void sort();

        const std::vector<int>& get_vector() const;
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v);

#endif
