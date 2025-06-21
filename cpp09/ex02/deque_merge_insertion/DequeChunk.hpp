#ifndef DEQUE_CHUNK_HPP
# define DEQUE_CHUNK_HPP

# include <deque>

class DequeChunk
{
    private:
        std::deque<int> data;

    public:
        DequeChunk();
        DequeChunk(const DequeChunk& other);
        DequeChunk& operator=(const DequeChunk& other);
        ~DequeChunk();

        DequeChunk(const std::deque<int>& left_data, const std::deque<int>& right_data);
        DequeChunk(const std::deque<int>& data);
        DequeChunk(int data);

        int                     get_key() const;
        const std::deque<int>&  get_data() const;
        size_t                  get_size() const;

        bool operator<(const DequeChunk& other) const;
        bool operator>(const DequeChunk& other) const;

        void copy_both_halves(DequeChunk* lesser, DequeChunk* greater) const;
};

std::ostream& operator<<(std::ostream& os, const DequeChunk& c);

#endif
