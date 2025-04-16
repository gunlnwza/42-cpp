#include <iostream>

#include <vector>
#include <array>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>

#include "easyfind.hpp"

int f(int x)
{
	return ((x + 1) * 10);
}

template <typename T>
void	try_to_find(const char* container_name, T& container, int item)
{
	typename T::iterator it;
	
	// std::cout << container_name << ": "; 
	// it = std::find(container.begin(), container.end(), item);
	// if (it != container.end())
	// 	std::cout << "FOUND! (*it = " << *it << ")" << std::endl;
	// else
	// 	std::cout << "Not found..." << std::endl;

	std::cout << container_name << ": ";
	try
	{
		it = easyfind(container, item);
		std::cout << "FOUND! (*it = " << *it << ")" << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Not found..." << std::endl;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./easyfind <item>" << std::endl;
		return (1);
	}
	const int	N = 4;
	const int	item = std::atoi(argv[1]);

	std::vector<int> vector;
	for (int i = 0; i < N; i++)
		vector.push_back(f(i));
	try_to_find("vector", vector, item);

	std::array<int, N> array;
	for (int i = 0; i < N; i++)
		array[i] = f(i);
	try_to_find("array", array, item);

	std::list<int> list;
	for (int i = 0; i < N; i++)
		list.push_back(f(i));
	try_to_find("list", list, item);

	std::deque<int> deque;
	for (int i = 0; i < N; i++)
		deque.push_back(f(i));
	try_to_find("deque", deque, item);

	std::forward_list<int> forward_list;
	for (int i = 0; i < N; i++)
		forward_list.push_front(f(i));
	try_to_find("forward_list", forward_list, item);

	std::set<int> set;
	for (int i = 0; i < N; i++)
		set.insert(f(i));
	try_to_find("set", set, item);

	std::unordered_set<int> unordered_set;
	for (int i = 0; i < N; i++)
		unordered_set.insert(f(i));
	try_to_find("unordered_set", set, item);

	return (0);
}
