#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <string>

typedef enum e_scalar_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
}	t_scalar_type;

typedef struct s_result
{
	std::string	char_message;
	std::string	int_message;
	std::string	float_message;
	std::string	double_message;
}	t_result;

class ScalarConverter
{
	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter(void);

	public:
		static void	convert(const std::string& literal);
};

#endif
