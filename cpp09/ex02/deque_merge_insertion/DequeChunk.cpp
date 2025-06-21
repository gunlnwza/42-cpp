#include <iostream>
#include "DequeChunk.hpp"

DequeChunk::DequeChunk() {}

DequeChunk::DequeChunk(const DequeChunk& other)
: data(other.data)
{}

DequeChunk& DequeChunk::operator=(const DequeChunk& other)
{
    this->data = other.data;
    return (*this);
}

DequeChunk::~DequeChunk() {}


DequeChunk::DequeChunk(const std::deque<int>& left_data, const std::deque<int>& right_data)
{
    this->data = left_data;
    this->data.insert(this->data.end(), right_data.begin(), right_data.end());
}

DequeChunk::DequeChunk(const std::deque<int>& data)
{
    this->data = data;
}

DequeChunk::DequeChunk(int data) {
    this->data.push_back(data);
}


int DequeChunk::get_key() const
{
    if (this->data.size() == 0)
        throw (std::runtime_error("chunk is empty"));
    return (this->data.back());
}

const std::deque<int>& DequeChunk::get_data() const
{
    return (this->data);
}

size_t DequeChunk::get_size() const
{
    return (this->data.size());
}

bool DequeChunk::operator<(const DequeChunk& other) const
{
    return (this->get_key() < other.get_key());
}

bool DequeChunk::operator>(const DequeChunk& other) const
{
    return (this->get_key() > other.get_key());
}


// assume 'lesser', and 'greater' are uninitialized
void DequeChunk::copy_both_halves(DequeChunk* lesser, DequeChunk* greater) const
{
    size_t lesser_size = this->data.size() / 2;
    for (size_t i = 0; i < this->data.size(); ++i)
    {
        if (i < lesser_size)
            lesser->data.push_back(this->data.at(i));
        else
            greater->data.push_back(this->data.at(i));
    }
}

// usage: std::cout << "chunk: " << chunk << std::endl;
std::ostream& operator<<(std::ostream& os, const DequeChunk& c)
{
    std::deque<int> data = c.get_data();
    std::cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i];
        if (i < data.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]";
    return (os);
}
