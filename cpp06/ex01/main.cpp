#include <iostream>
#include "Serializer.hpp"

std::ostream&	operator<<(std::ostream& os, const Data &data)
{
	os << data.number << "," << data.name << "," << data.current_project;
	return (os);
}

int	main(void)
{
	Data	original_data = {42, "Gun", "cpp06"};

	Data*		ptr = &original_data;
	uintptr_t	raw = Serializer::serialize(ptr);
	Data*		deserialized_ptr = Serializer::deserialize(raw);

	std::cout << "original_data     : " << original_data << std::endl
			  << "ptr               : " << ptr << std::endl
			  << "raw               : " << raw << std::endl
			  << "deserialized_ptr  : " << deserialized_ptr << std::endl
			  << "*deserialized_ptr : " << *deserialized_ptr << std::endl;

	return (0);
}
