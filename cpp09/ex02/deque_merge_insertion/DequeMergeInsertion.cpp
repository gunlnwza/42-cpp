#include "DequeMergeInsertion.hpp"


DequeMergeInsertion::DequeMergeInsertion()
{
    this->name = "std::deque";
}

DequeMergeInsertion::DequeMergeInsertion(const DequeMergeInsertion& other)
: ISortStrategy(other)
{
    *this = other;
}

DequeMergeInsertion& DequeMergeInsertion::operator=(const DequeMergeInsertion& other)
{
    this->deque = other.deque;
    return (*this);
}

DequeMergeInsertion::~DequeMergeInsertion()
{}


void DequeMergeInsertion::copy_numbers(const std::vector<int>& inputs)
{
    this->deque.assign(inputs.begin(), inputs.end());
}

std::vector<int> DequeMergeInsertion::get_numbers() const
{
    std::vector<int> vec;

    vec.assign(this->deque.begin(), this->deque.end());
    return (vec);
}


// combine two chunks into one big chunk, with lesser-valued chunk on the left
void DequeMergeInsertion::_make_pairs(std::deque<DequeChunk*>& chunks, std::deque<DequeChunk*>& pairs, DequeChunk** chunk)
{
    DequeChunk* lesser;
    DequeChunk* greater;

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
        pairs.push_back(new DequeChunk(lesser->get_data(), greater->get_data()));
    }
    if (chunks.size() % 2 == 0)
        *chunk = NULL;
    else
        *chunk = new DequeChunk(chunks[chunks.size() - 1]->get_data());
    
}

// divide pairs into 'to_insert' (line of lesser-valued chunk) and 'main_chain' (line of greater-valued chunk)
void DequeMergeInsertion::_divide_pairs(std::deque<DequeChunk*>& pairs, DequeChunk* chunk, std::deque<DequeChunk*>& to_insert, std::deque<DequeChunk*>& main_chain)
{
    DequeChunk* lesser;
    DequeChunk* greater;

    for (std::deque<DequeChunk*>::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        lesser = new DequeChunk();
        greater = new DequeChunk();
        (*it)->copy_both_halves(lesser, greater);
        delete *it;

        to_insert.push_back(lesser);
        main_chain.push_back(greater);
    }
    if (chunk)
        to_insert.push_back(chunk);
}

// binary-search the index to insert i-th item, with the most optimal i-th item picking order
void DequeMergeInsertion::_insert_to_main_chain(std::deque<DequeChunk*>& to_insert, std::deque<DequeChunk*>& main_chain)
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

// sort the chunks, recursively
void DequeMergeInsertion::_merge_insertion(std::deque<DequeChunk*>& chunks)
{
    if (chunks.size() <= 1)
        return ;

    std::deque<DequeChunk*> pairs;
    DequeChunk*              chunk;
    std::deque<DequeChunk*> to_insert;
    std::deque<DequeChunk*> main_chain;

    this->_make_pairs(chunks, pairs, &chunk);
    this->_merge_insertion(pairs);
    this->_divide_pairs(pairs, chunk, to_insert, main_chain);    
    this->_insert_to_main_chain(to_insert, main_chain);
    for (std::deque<DequeChunk*>::iterator it = chunks.begin(); it != chunks.end(); ++it)
        delete *it;
    chunks = main_chain;
}

void DequeMergeInsertion::sort()
{
    std::deque<DequeChunk*> chunks;

    this->compare_count = 0;

    for (std::deque<int>::iterator it = this->deque.begin(); it != this->deque.end(); ++it)
        chunks.push_back(new DequeChunk(*it));

    this->_merge_insertion(chunks);

    this->deque.clear();
    for (std::deque<DequeChunk*>::iterator it = chunks.begin(); it != chunks.end(); ++it)
    {
        this->deque.push_back((*it)->get_key());
        delete *it;
    }
}
