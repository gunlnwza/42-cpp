#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

template <typename T>
void	iter(T* arr, size_t len, void (*func)(T&))
{
	for (size_t i = 0; i < len; i++)
		func(arr[i]);
}

template <typename T>
void	iter(const T* arr, size_t len, void (*func)(const T&))
{
	for (size_t i = 0; i < len; i++)
		func(arr[i]);
}

// ---

template <typename T>
void	print_item(const T& item)
{
	std::cout << item << ",";
}

template <typename T>
void	plus_self(T& item)
{
	item += item;
}

#endif
