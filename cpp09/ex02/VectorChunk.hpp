#ifndef VECTOR_CHUNK_HPP
# define VECTOR_CHUNK_HPP

# include <vector>

class VectorChunk
{
    private:
        int                 key;
        std::vector<int>    data;
        size_t              size;

    public:
        VectorChunk();
        ~VectorChunk();
        // TODO: implement OCF

        VectorChunk(const std::vector<int>& left_data, const std::vector<int>& right_data);
        VectorChunk(const std::vector<int>& data);
        VectorChunk(int data);

        int get_key() const;
        std::vector<int> get_data() const;
        size_t get_size() const;
        bool operator<(const VectorChunk& other) const;
        bool operator>(const VectorChunk& other) const;

        void divide_into(VectorChunk& lesser, VectorChunk& greater);
};

#endif
