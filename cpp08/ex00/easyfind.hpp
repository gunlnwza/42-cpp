#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator	it;

	it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::runtime_error("Value not found in container");
	return (it);
}

// template <typename T>
// typename T::iterator easyfind(const T& arr, int value)
// {
// 	size_t					len;
// 	typename T::iterator	it;

// 	len = sizeof(arr) / sizeof(arr[0]);
// 	it = std::find(arr, arr + len, value);
// 	if (it != arr + len)
// 		throw std::runtime_error("Value not found in container");
// 	return (it);
// }

#endif
