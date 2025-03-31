#include "iter.hpp"

int	main(void)
{
	size_t	len;

	// ---
	int		nums[] = {1, 2, 3, 4, 5, 6, 7, 8};
	len = sizeof(nums) / sizeof(nums[0]);

	iter(nums, len, print_item);
	std::cout << std::endl;

	iter(nums, len, plus_self);
	
	iter(nums, len, print_item);
	std::cout << std::endl
			  << std::endl;

	// ---
	std::string	strs[] = {"42", "Bangkok", "Is", "Awesome"};
	len = sizeof(strs) / sizeof(strs[0]);

	iter(strs, len, print_item);
	std::cout << std::endl;

	iter(strs, len, plus_self);
	
	iter(strs, len, print_item);
	std::cout << std::endl
			  << std::endl;

	// ---

	const std::string const_strs[] = {"You", "Shall", "Not", "Modify!"};
	len = sizeof(const_strs) / sizeof(const_strs[0]);
	
	iter(const_strs, len, print_item);

	// iter(const_strs, len, plus_self);  // do not un-comment!

	// ---

	return (0);
}
