#include "VectorMergeInsertion.hpp"

#include <iostream>


VectorMergeInsertion::VectorMergeInsertion()
{
    this->name = "std::vector";
}

VectorMergeInsertion::VectorMergeInsertion(const VectorMergeInsertion& other)
: ISortStrategy(other)
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


// combine two chunks into one big chunk, with lesser-valued chunk on the left
void VectorMergeInsertion::_make_pairs(std::vector<VectorChunk*>& chunks, std::vector<VectorChunk*>& pairs, VectorChunk** chunk)
{
    VectorChunk* lesser;
    VectorChunk* greater;

    for (size_t i = 0; i < chunks.size() - 1; i += 2)
    {
        this->compare_count++;
        if (*(chunks[i]) < *(chunks[i + 1]))
        {
            lesser = chunks[i];
            greater = chunks[i + 1];
        }
        else
        {
            lesser = chunks[i + 1];
            greater = chunks[i];
        }
        pairs.push_back(new VectorChunk(lesser->get_data(), greater->get_data()));
    }
    if (chunks.size() % 2 == 0)
        *chunk = NULL;
    else
        *chunk = new VectorChunk(chunks[chunks.size() - 1]->get_data());
    
}

// divide pairs into 'to_insert' (line of lesser-valued chunk) and 'main_chain' (line of greater-valued chunk)
void VectorMergeInsertion::_divide_pairs(std::vector<VectorChunk*>& pairs, VectorChunk* chunk, std::vector<VectorChunk*>& to_insert, std::vector<VectorChunk*>& main_chain)
{
    VectorChunk* lesser;
    VectorChunk* greater;

    for (std::vector<VectorChunk*>::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        lesser = new VectorChunk();
        greater = new VectorChunk();
        (*it)->copy_both_halves(lesser, greater);
        delete *it;

        to_insert.push_back(lesser);
        main_chain.push_back(greater);
    }
    if (chunk)
        to_insert.push_back(chunk);
}

// binary-search the index to insert i-th item, with the most optimal i-th item picking order
void VectorMergeInsertion::_insert_to_main_chain(std::vector<VectorChunk*>& to_insert, std::vector<VectorChunk*>& main_chain)
{
    JacobsthalDecreasingGenerator gen;
    size_t  i;
    int     left;
    int     right;
    int     mid;
    int     insert_idx;

    for (size_t chunk_inserted = 0; chunk_inserted < to_insert.size(); ++chunk_inserted)
    {
        i = gen.next() - 1;
        while (i >= to_insert.size())
            i = gen.next() - 1;

        left = 0;
        right = chunk_inserted + i;
        while (left < right)
        {
            mid = left + (right - left) / 2;
            this->compare_count++;
            if (*(to_insert[i]) < *(main_chain[mid]))
                right = mid;
            else
                left = mid + 1;
        }
        insert_idx = right;
        main_chain.insert(main_chain.begin() + insert_idx, to_insert[i]);
    }
}

// // for debugging
// static void indent(int depth)
// {
//     for (int i = 0; i < depth; ++i)
//         std::cout << "    ";
// }

// // usage: std::cout << "chunks: " << chunks << std::endl;
// static std::ostream& operator<<(std::ostream& os, const std::vector<VectorChunk*>& chunks)
// {
//     for (std::vector<VectorChunk*>::const_iterator it = chunks.begin(); it != chunks.end(); ++it)
//     {
//         if (it != chunks.begin())
//             os << " ";
//         os << **it;
//     }
//     return (os);
// }

// sort the chunks, recursively
// (uncomment to see it in action!)
void VectorMergeInsertion::_merge_insertion(std::vector<VectorChunk*>& chunks, int depth)
{
    if (chunks.size() <= 1)
        return ;

    std::vector<VectorChunk*> pairs;
    VectorChunk*              chunk;
    std::vector<VectorChunk*> to_insert;
    std::vector<VectorChunk*> main_chain;

    // indent(depth); std::cout << "chunks    = " << chunks << std::endl;

    this->_make_pairs(chunks, pairs, &chunk);
    // indent(depth); std::cout << "pairs     = " << pairs << std::endl;

    this->_merge_insertion(pairs, depth + 1);
    // indent(depth); std::cout << "pairs     = " << pairs << std::endl;

    this->_divide_pairs(pairs, chunk, to_insert, main_chain);    
    // indent(depth); std::cout << "to_insert = " << to_insert << " ; "; std::cout << "main_chain = " << main_chain << std::endl;

    this->_insert_to_main_chain(to_insert, main_chain);
    for (std::vector<VectorChunk*>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        delete *it;
    chunks = main_chain;
    // indent(depth); std::cout << "chunks    = " << chunks << std::endl;
}

void VectorMergeInsertion::sort()
{
    std::vector<VectorChunk*> chunks;

    this->compare_count = 0;

    for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it)
        chunks.push_back(new VectorChunk(*it));

    this->_merge_insertion(chunks, 1);

    this->vector.clear();
    for (std::vector<VectorChunk*>::iterator it = chunks.begin(); it != chunks.end(); ++it)
    {
        this->vector.push_back((*it)->get_key());
        delete *it;
    }
}
