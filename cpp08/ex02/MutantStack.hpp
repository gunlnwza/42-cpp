#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
	private:
		std::stack<T>::iterator it;

	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack<T>& operator=(const MutantStack& other);
		~MutantStack();

		MutantStack<T>::iterator	begin();
		MutantStack<T>::iterator	end();

		// override push? must update begin()
		// override pop? must update end()
};

# include "MutantStack.tpp"

#endif
