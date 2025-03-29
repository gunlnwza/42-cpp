#include "ScalarConverter.hpp"

void	batch_test(void)
{
	int			i;
	int			len;
	const char *inputs[] = {
		"# 🔠 CHAR",
		"a", "b", " ",
		"# 🔢 INT",
		"1", "2", "3", "42", "127", "-128", "128", "-129", "200", "-200",
		"2147483647", "-2147483648", "2147483648", "-2147483649",
		"9223372036854775807", "-9223372036854775808", "9223372036854775808", "-9223372036854775809",
		"# 🛟 FLOAT",
		"123.456f", "0.0f", "inff", "+inff", "-inff", "nanf",
		"# 🛟🛟 DOUBLE",
		"123.456", "0.0", "inf", "+inf", "-inf", "nan"
	};

	i = 0;
	len = sizeof(inputs) / sizeof(inputs[0]);
	while (i < len)
	{
		if (inputs[i][0] == '#')
		{
			std::cout << std::endl
					  << "========================================" << std::endl
					  << inputs[i] << std::endl
					  << "========================================" << std::endl;
			i++;
			continue ;
		}
		std::cout << "[ " << inputs[i] << " ]" << std::endl;
		ScalarConverter::convert(inputs[i]);
		std::cout << "----------------------------------------" << std::endl;
		i++;
	}
}

int	main(int argc, char **argv)
{
	std::string	input;

	if (argc != 2)
	{
		std::cerr << "Usage: ./scalar_converter [<literal> | --batch-test | -b]" << std::endl;
		return (EXIT_FAILURE);
	}
	input = argv[1];
	if (input.compare("--batch-test") == 0 || input.compare("-b") == 0)
		batch_test();
	else
		ScalarConverter::convert(argv[1]);
	return (EXIT_SUCCESS);
}
