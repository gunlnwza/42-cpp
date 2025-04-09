#ifndef ARRAY_TPP
# define ARRAY_TPP

# include "Array.hpp"

template <typename T>
Array<T>::Array() : data(NULL), len(0)
{
	// std::cout << "default constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n) : data(new T[n]()), len(n)
{
	// std::cout << "constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(const Array<T>& other) : data(new T[other.len]()), len(other.len)
{
	// std::cout << "copy constructor called" << std::endl;

	for (unsigned int i = 0; i < other.len; i++)
		this->data[i] = other.data[i];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this == &other)
	{
		return (*this);
	}
	// std::cout << "copy assignment called" << std::endl;

	delete[] this->data;

	this->len = other.len;
	this->data = new T[other.len]();
	for (unsigned int i = 0; i < other.len; i++)
		this->data[i] = other.data[i];

	return (*this);
}

template <typename T>
Array<T>::~Array()
{
	// std::cout << "destructor called" << std::endl;

	delete[] this->data;
}


template <typename T>
T& Array<T>::operator[](int i)
{
	if (i < 0)
		i += this->len;
	if (i < 0 || static_cast<unsigned int>(i) >= this->len)
		throw (std::out_of_range("Index out of range, cannot access"));
	return (this->data[i]);
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (this->len);
}

#endif
