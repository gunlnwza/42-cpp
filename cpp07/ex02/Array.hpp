#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T>
class Array
{
	private:
		T*				data;
		unsigned int	len;
		unsigned int	capacity;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array<T>& other);
		Array& operator=(const Array<T>& other);
		~Array();

		T& operator[](int i);
		unsigned int size() const;
};

# include "Array.tpp"

#endif
