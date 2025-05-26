#include "VectorMergeInsertion.hpp"

#include <iostream>

#define DEBUG true


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


static void indent(int depth)
{
    for (int i = 0; i < depth; ++i)
        std::cout << "    ";
}

std::ostream& operator<<(std::ostream& os, std::vector<VectorChunk> v_c)
{
    for (std::vector<VectorChunk>::iterator it = v_c.begin(); it != v_c.end(); ++it)
    {
        if (it != v_c.begin())
            os << " ";
        os << *it;
    }
    return (os);
}

void VectorMergeInsertion::_make_pairs(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& chunks)
{
    for (size_t i = 0; i < chunks.size() - 1; i += 2)
    {
        this->compare_count++;
        if (chunks[i] < chunks[i + 1])
            pairs.push_back(VectorChunk(chunks[i].get_data(), chunks[i + 1].get_data()));
        else
            pairs.push_back(VectorChunk(chunks[i + 1].get_data(), chunks[i].get_data()));
    }
}

void VectorMergeInsertion::_divide_pairs(std::vector<VectorChunk>& pairs, std::vector<VectorChunk>& chunks, std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain)
{
    VectorChunk lesser;
    VectorChunk greater;

    for (std::vector<VectorChunk>::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        it->divide_into(lesser, greater);
        to_insert.push_back(lesser);
        main_chain.push_back(greater);
    }
    if (chunks.size() % 2 == 1)  // TODO: make heap alloc later (set NULL for remainder chunk if even chunk.size())
        to_insert.push_back(chunks.at(chunks.size() - 1));
}

void VectorMergeInsertion::_insert_to_main_chain(std::vector<VectorChunk>& to_insert, std::vector<VectorChunk>& main_chain)
{
    JacobsthalDecreasingGenerator gen;
    size_t  i;
    int     l;
    int     r;
    int     m;
    int     insert_idx;

    for (size_t chunk_inserted = 0; chunk_inserted < to_insert.size(); ++chunk_inserted)
    {
        i = gen.next() - 1;
        while (i >= to_insert.size())
            i = gen.next() - 1;
        l = 0;
        r = chunk_inserted + i;
        while (l < r)
        {
            m = l + (r - l) / 2;
            this->compare_count++;
            if (to_insert[i] < main_chain[m])
                r = m;
            else
                l = m + 1;
        }
        insert_idx = r;
        main_chain.insert(main_chain.begin() + insert_idx, to_insert[i]);
    }
}

void VectorMergeInsertion::_merge_insertion(std::vector<VectorChunk>& chunks, int depth) // TODO: remove depth variable
{
    if (chunks.size() <= 1)
        return ;

    std::vector<VectorChunk> pairs;
    std::vector<VectorChunk> to_insert;
    std::vector<VectorChunk> main_chain;

    if (DEBUG) {
        indent(depth); std::cout << "chunks    = " << chunks << std::endl;
    }

    this->_make_pairs(pairs, chunks);
    if (DEBUG) {
        indent(depth); std::cout << "pairs     = " << pairs << std::endl;
    }

    this->_merge_insertion(pairs, depth + 1);
    if (DEBUG) {
        indent(depth); std::cout << "pairs     = " << pairs << std::endl;
    }
    
    this->_divide_pairs(pairs, chunks, to_insert, main_chain);
    if (DEBUG) {
        indent(depth); std::cout << "to_insert = " << to_insert << " ; " << "main_chain = " << main_chain << std::endl;
    }
    
    this->_insert_to_main_chain(to_insert, main_chain);
    chunks = main_chain;
    if (DEBUG) {
        indent(depth); std::cout << "chunks    = " << chunks << std::endl;
    }
}

void VectorMergeInsertion::sort()
{
    std::vector<VectorChunk> chunks;

    this->compare_count = 0;    
    for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it)
        chunks.push_back(VectorChunk(*it));
    this->_merge_insertion(chunks, 1);
    this->vector.clear();
    for (std::vector<VectorChunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        this->vector.push_back(it->get_key());
}
