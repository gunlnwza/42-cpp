#include "VectorChunk.hpp"

#include <iostream>

VectorChunk::VectorChunk() {}
VectorChunk::~VectorChunk() {}

VectorChunk::VectorChunk(const std::vector<int>& left_data, const std::vector<int>& right_data) {
    this->data = left_data;
    this->data.insert(this->data.end(), right_data.begin(), right_data.end());
}

VectorChunk::VectorChunk(const std::vector<int>& data) {
    this->data = data;
}

VectorChunk::VectorChunk(int data) {
    this->data.push_back(data);
}


int VectorChunk::get_key() const {
    // std::cout << "getting key" << std::endl;
    if (this->data.size() == 0)
        throw (std::runtime_error("chunk is empty"));
    return (this->data.back());
}

std::vector<int> VectorChunk::get_data() const {
    // std::cout << "getting data" << std::endl;
    return (this->data);
}

size_t VectorChunk::get_size() const {
    // std::cout << "getting size" << std::endl;
    return (this->data.size());
}

bool VectorChunk::operator<(const VectorChunk& other) const {
    return (this->get_key() < other.get_key());
}

bool VectorChunk::operator>(const VectorChunk& other) const {
    return (this->get_key() > other.get_key());
}


void VectorChunk::divide_into(VectorChunk& lesser, VectorChunk& greater)
{
    lesser.data.clear();
    greater.data.clear();
    size_t n = this->data.size() / 2;
    for (size_t i = 0; i < this->data.size(); ++i)
    {
        if (i < n)
            lesser.data.push_back(this->data.at(i));
        else
            greater.data.push_back(this->data.at(i));
    }
}

std::ostream& operator<<(std::ostream& os, const VectorChunk& c)
{
    std::vector<int> data = c.get_data();
    std::cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i];
        if (i < data.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]";
    return (os);
}
