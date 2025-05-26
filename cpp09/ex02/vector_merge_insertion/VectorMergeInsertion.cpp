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
    this->vector = inputs;
}

std::vector<int> VectorMergeInsertion::get_numbers() const
{
    return (this->vector);
}


void debug(int depth, const std::string& msg) {
    for (int i = 0; i < depth; ++i) {
        std::cout << "    ";
    }
    std::cout << msg << std::endl;
}

void make_pairs(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& chunks)
{
    // debug(depth, "(1) make pairs");
    for (size_t i = 0; i < chunks.size() - 1; i += 2)
    {
        if (chunks[i] < chunks[i + 1])
            pairs.push_back(VectorChunk(chunks[i].get_data(), chunks[i + 1].get_data()));
        else
            pairs.push_back(VectorChunk(chunks[i + 1].get_data(), chunks[i].get_data()));
    }
}

void init_to_insert_and_main_chain(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain)
{
    VectorChunk lesser;
    VectorChunk greater;

    for (std::vector<VectorChunk>::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        it->divide_into(lesser, greater);
        to_insert.push_back(lesser);
        main_chain.push_back(greater);
    }
}

void insert_to_main_chain(std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain)
{
    // debug(depth, "(3.2) inserting");
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
}

void VectorMergeInsertion::_merge_insertion(std::vector<VectorChunk>& chunks, int depth)
{
    // debug(depth, "_merge_insertion");
    if (depth == 40)
        throw (std::runtime_error("too many recursion"));

    for (int i = 0; i < depth; ++i)
        std::cout << "    ";
    for (std::vector<VectorChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    if (chunks.size() <= 1) {
        return ;
    }

    std::vector<VectorChunk> pairs;
    make_pairs(pairs, chunks);

    // debug(depth, "(2) call deeper _merge_insertion");
    this->_merge_insertion(pairs, depth + 1);

    std::vector<VectorChunk> to_insert, main_chain;
    init_to_insert_and_main_chain(pairs, to_insert, main_chain);
    if (chunks.size() % 2 == 1) {  // TODO: make heap alloc later
        to_insert.push_back(chunks.at(chunks.size() - 1));
    }

    insert_to_main_chain(to_insert, main_chain);
    
    chunks = main_chain;

    for (int i = 0; i < depth; ++i)
        std::cout << "    ";
    for (std::vector<VectorChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void VectorMergeInsertion::sort()
{
    this->compare_count = 0;

    // std::cout << "init chunk" << std::endl;
    
    std::vector<VectorChunk> chunks;
    for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it) {
        chunks.push_back(VectorChunk(*it));
    }

    this->_merge_insertion(chunks, 1);

    // std::cout << "push to vector" << std::endl;

    this->vector.clear();
    for (std::vector<VectorChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it) {
        this->vector.push_back(it->get_key());
    }
}
