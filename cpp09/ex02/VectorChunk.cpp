#include "VectorChunk.hpp"

#include <iostream>


VectorChunk::VectorChunk() : key(0), size(0) {}
VectorChunk::~VectorChunk() {}

VectorChunk::VectorChunk(const std::vector<int>& left_data, const std::vector<int>& right_data) {
    this->key = right_data.back();
    this->data = left_data;
    this->data.insert(this->data.end(), right_data.begin(), right_data.end());
    this->size = left_data.size() + right_data.size();
}

VectorChunk::VectorChunk(const std::vector<int>& data) {
    this->key = data.back();
    this->data = data;
    this->size = data.size();
}

VectorChunk::VectorChunk(int data) {
    this->key = data;
    this->data.push_back(data);
    this->size = 1;
}


int VectorChunk::get_key() const {
    return (this->key);
}

std::vector<int> VectorChunk::get_data() const {
    return (this->data);
}

size_t VectorChunk::get_size() const {
    return (this->size);
}

bool VectorChunk::operator<(const VectorChunk& other) const {
    return (this->key < other.key);
}

bool VectorChunk::operator>(const VectorChunk& other) const {
    return (this->key > other.key);
}


void VectorChunk::divide_into(VectorChunk& lesser, VectorChunk& greater)
{
    std::cout << "lesser.data.clear();" << std::endl;
    lesser.data.clear();
    std::cout << "greater.data.clear();" << std::endl;
    greater.data.clear();

    for (std::vector<int>::iterator it = this->data.begin(); it != this->data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "size_t n = this->size / 2;" << std::endl;
    size_t n = this->size / 2;
    std::cout <<" HI HELLO" << std::endl;
    for (size_t i = 0; i < this->size; ++i)
    {
        if (i < n) {
            std::cout << "inserting data to lesser" << std::endl;
            lesser.data.push_back(this->data.at(i));
        }
        else {
            std::cout << "inserting data to greater" << std::endl;
            greater.data.push_back(this->data.at(i));
        }
    }
}
