#include "VectorMergeInsertion.hpp"

#include <iostream>


VectorMergeInsertion::VectorMergeInsertion()
{
    this->name = "std::vector";
}

VectorMergeInsertion::VectorMergeInsertion(const VectorMergeInsertion& other)
{
    *this = other;
}

VectorMergeInsertion& VectorMergeInsertion::operator=(const VectorMergeInsertion& other)
{
    this->vector = other.vector;
    return (*this);
}

VectorMergeInsertion::~VectorMergeInsertion()
{}


void VectorMergeInsertion::copy_numbers(const std::vector<int>& inputs)
{
    // std::cout << "copy vector" << std::endl;
    this->vector = inputs;
}

std::vector<int> VectorMergeInsertion::get_numbers() const
{
    return (this->vector);
}


void VectorMergeInsertion::_merge_insertion(std::vector<VectorChunk>& chunks)
{
    std::cout << "_merge_insertion" << std::endl;

    if (chunks.size() == 1) {
        std::cout << "chunk.size() == 1, returning" << std::endl;
        return ;
    }

    std::cout << "(1) make pairs" << std::endl;

    std::vector<VectorChunk> pairs;
    VectorChunk remainder_chunk;
    for (size_t i = 0; i < chunks.size() - 1; i += 2)
    {
        VectorChunk pair;
        if (chunks[i] < chunks[i + 1])
            pair = VectorChunk(chunks[i].get_data(), chunks[i + 1].get_data());
        else
            pair = VectorChunk(chunks[i + 1].get_data(), chunks[i].get_data());
        pairs.push_back(pair);
    }
    if (chunks.size() % 2 == 1) {
        remainder_chunk = chunks.back();
    }

    std::cout << "(2) lower _merge_insertion" << std::endl;
    this->_merge_insertion(pairs);

    std::cout << "(3.1) init to_insert and main_chain" << std::endl;
    std::vector<VectorChunk> main_chain;
    std::vector<VectorChunk> to_insert;
    VectorChunk lesser, greater;
    for (std::vector<VectorChunk>::iterator it; it != pairs.end(); ++it) {
        std::cout << "divide_into" << std::endl;
        it->divide_into(lesser, greater);
        std::cout << "to_insert.push_back(lesser);" << std::endl;
        to_insert.push_back(lesser);
        std::cout << "main_chain.push_back(greater);" << std::endl;
        main_chain.push_back(greater);
    }

    if (chunks.size() % 2 == 1) { 
        std::cout << "(3.1.5) insert remainder_chunk" << std::endl;
        to_insert.push_back(remainder_chunk);
    }

    std::cout << "(3.2) inserting" << std::endl;
    // int chunk_inserted = 0;
    for (size_t i = 0; i < to_insert.size(); ++i)
    {
        int insert_idx = main_chain.size();
        for (size_t j = 0; j < main_chain.size(); ++j)
        {
            if (to_insert[i] < main_chain[j]) {
                insert_idx = j;
                break ;
            }
        }
        main_chain.insert(main_chain.begin() + insert_idx, to_insert[i]);
    }

    chunks = main_chain;
}

void VectorMergeInsertion::sort()
{
    this->compare_count = 0;

    std::cout << "init chunk" << std::endl;
    
    std::vector<VectorChunk> chunks;
    for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it) {
        chunks.push_back(VectorChunk(*it));
    }

    this->_merge_insertion(chunks);

    std::cout << "push to vector" << std::endl;

    this->vector.clear();
    for (std::vector<VectorChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it) {
        this->vector.push_back(it->get_key());
    }
}
