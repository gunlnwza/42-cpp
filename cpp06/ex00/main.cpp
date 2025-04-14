#include <iostream>

#include "ScalarConverter.hpp"


void	type_test(size_t size_, const char **inputs, const char *banner_message)
{
	std::cout << "========================================" << std::endl
			  <<  banner_message 							<< std::endl
			  << "========================================" << std::endl;

	size_t i = 0;
	while (i < size_)
	{
		std::cout << "> '" << inputs[i] << "'" << std::endl;
		ScalarConverter::convert(inputs[i]);
		std::cout << "----------------------------------------" << std::endl;
		i++;
	}
}

void	batch_test(char *option)
{
	const char	*chars[] = {
		"a", "b", " ",
	};
	const char	*ints[] = {
		"1", "2", "3", "42", "127", "-128", "128", "-129", "200", "-200",
		"2147483647", "-2147483648", "2147483648", "-2147483649",
		"9223372036854775807", "-9223372036854775808", "9223372036854775808", "-9223372036854775809",
	};
	const char	*floats[] = {
		"123.456f", "0.0f", "inff", "+inff", "-inff", "nanf",
	};
	const char	*doubles[] = {
		"123.456", "0.0", "inf", "+inf", "-inf", "nan"
	};

	bool	test_char, test_int, test_float, test_double;
	option++;
	while (*option)
	{
		if (*option == 'b')
		{
			test_char = true;
			test_int = true;
			test_float = true;
			test_double = true;
		}
		else if (*option == 'c')
			test_char = true;
		else if (*option == 'i')
			test_int = true;
		else if (*option == 'f')
			test_float = true;
		else if (*option == 'd')
			test_double = true;
		option++;
	}

	if (test_char)
		type_test(sizeof(chars) / sizeof(chars[0]), chars, "🔠 CHAR");
	if (test_int)
		type_test(sizeof(ints) / sizeof(ints[0]), ints, "🔢 INT");
	if (test_float)
		type_test(sizeof(floats) / sizeof(floats[0]), floats, "🛟 FLOAT");
	if (test_double)
		type_test(sizeof(doubles) / sizeof(doubles[0]), doubles, "🛟🛟 DOUBLE");
}


int	main(int argc, char **argv)
{
	std::string	input;

	if (argc != 2)
	{
		std::cerr << "Usage: ./scalar_converter [ <literal> | -b | -c | -i | -f | -d ]" << std::endl;
		return (EXIT_FAILURE);
	}
	if (*(argv[1]) == '-')
	{
		batch_test(argv[1]);
		return (EXIT_SUCCESS);
	}

	input = argv[1];
	ScalarConverter::convert(argv[1]);
	
	return (EXIT_SUCCESS);
}
