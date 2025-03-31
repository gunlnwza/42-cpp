#ifndef ARRAY_TPP
# define ARRAY_TPP

# include "Array.hpp"

template <typename T>
Array<T>::Array()
: data(nullptr), len(0), capacity(0)
{}

template <typename T>
Array<T>::Array(unsigned int n)
: len(0), capacity(n)
{
	this->data = new T[n]();
}

template <typename T>
Array<T>::Array(const Array<T>& other)
: len(other.len), capacity(other.capacity)
{
	this->data = new T[other.len]();
	for (unsigned int i = 0; i < len; i++)
	{
		this->data[i] = other.data[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	this->len = other.len;
	this->capacity = other.capacity;
	for (unsigned int i = 0; i < len; i++)
	{
		this->data[i] = other.data[i];
	}
}

template <typename T>
Array<T>::~Array()
{
	delete[] this->data;
}


template <typename T>
T& Array<T>::operator[](int i)
{
	if (i < 0 || static_cast<unsigned int>(i) >= this->len)
		throw (std::out_of_range("Index out of range"));
	return (this->data[i]);
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (this->len);
}

#endif
