#include "ScalarConverter.hpp"

int	batch_test(void)
{
	int			i;
	int			len;
	// const char *inputs[] = {
	// 	"1", "2", "3",
	// 	"2147483647", "2147483648",
	// 	"-2147483648", "-2147483649",
	// 	"9223372036854775807", "9223372036854775808",
	// 	"-9223372036854775808", "-9223372036854775809"
	// };
	const char *inputs[] = {
		"127", "-128", "128", "-129",
		"1", "42", "200", "-200"
	};

	i = 0;
	len = sizeof(inputs) / sizeof(inputs[0]);
	while (i < len)
	{
		std::cout << "[ " << inputs[i] << " ]" << std::endl;
		ScalarConverter::convert(inputs[i]);
		std::cout << "----------------------------------------" << std::endl;
		i++;
	}
	return	(EXIT_SUCCESS);
}

int	print_error(void)
{
	std::cerr << "Error: Expected 1 argument" << std::endl
			  << "Usage: ./scalar_converter <literal>" << std::endl;
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int	ret;

	if (argc != 2)
	{
		ret = batch_test();
		return (ret);
	}
	ScalarConverter::convert(argv[1]);
	return (EXIT_SUCCESS);
}
