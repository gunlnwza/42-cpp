#include <iostream>
#include <vector>

#include "easyfind.hpp"

int main(void)
{
	std::vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);

	std::cout << myvector[0] << std::endl;
	std::cout << myvector[1] << std::endl;
	std::cout << myvector[2] << std::endl;

	// std::cout << easyfind(myvector, 3) << std::endl;

	return 0;
}
