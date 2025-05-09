#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
    public:
        typedef typename std::stack<T>::container_type::iterator iterator;

        MutantStack();
        MutantStack(const MutantStack& other);
        MutantStack<T>& operator=(const MutantStack& other);
        ~MutantStack();

        iterator begin();
        iterator end();	
};

# include "MutantStack.tpp"

#endif
