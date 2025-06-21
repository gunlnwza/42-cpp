#ifndef VECTOR_CHUNK_HPP
# define VECTOR_CHUNK_HPP

# include <vector>
# include <iostream>

class VectorChunk
{
    private:
        std::vector<int> data;

    public:
        VectorChunk();
        VectorChunk(const VectorChunk& other);
        VectorChunk& operator=(const VectorChunk& other);
        ~VectorChunk();

        VectorChunk(const std::vector<int>& left_data, const std::vector<int>& right_data);
        VectorChunk(const std::vector<int>& data);
        VectorChunk(int data);

        int                     get_key() const;
        const std::vector<int>& get_data() const;
        size_t                  get_size() const;

        bool operator<(const VectorChunk& other) const;
        bool operator>(const VectorChunk& other) const;

        void copy_both_halves(VectorChunk* lesser, VectorChunk* greater) const;
};

std::ostream& operator<<(std::ostream& os, const VectorChunk& c);

#endif
