#include "ScalarConverter.hpp"

void	process_char(const std::string& input, struct ScalarFields& fields)
{
	fields.c = input[0];

	fields.i = static_cast<int>(fields.c);
	fields.f = static_cast<float>(fields.c);
	fields.d = static_cast<double>(fields.c);
}

void	process_int(const std::string& input, struct ScalarFields& fields)
{
	long long	temp;

	temp = std::atoll(input.c_str());

	if (temp < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < temp)
		fields.i_state = IMPOSSIBLE;
	if (!(0 <= temp && temp <= 255))
		fields.c_state = IMPOSSIBLE;

	fields.i = static_cast<int>(temp);
	fields.c = static_cast<char>(fields.i);
	fields.f = static_cast<float>(fields.i);
	fields.d = static_cast<double>(fields.i);

}

void	process_float(const std::string& input, struct ScalarFields& fields)
{
	fields.f = std::strtof(input.c_str(), NULL);

	if (input == "inff" || input == "-inff" || input == "nanf")
	{
		fields.c_state = IMPOSSIBLE;
		fields.i_state = IMPOSSIBLE;
	}

	fields.c = static_cast<char>(fields.f);
	fields.i = static_cast<int>(fields.f);
	fields.d = static_cast<double>(fields.f);
}

void	process_double(const std::string& input, struct ScalarFields& fields)
{
	errno = 0;

	fields.d = std::strtod(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		if (fields.f == std::numeric_limits<float>::infinity())
			std::cout << "float: overflow" << std::endl;
        else if (fields.f == 0.0f)
            std::cout << "float: underflow" << std::endl;
	}

	if (input == "inf" || input == "-inf" || input == "nan")
	{
		fields.c_state = IMPOSSIBLE;
		fields.i_state = IMPOSSIBLE;
	}
	
	fields.c = static_cast<char>(fields.d);
	fields.i = static_cast<int>(fields.d);
	fields.f = static_cast<float>(fields.d);
}
