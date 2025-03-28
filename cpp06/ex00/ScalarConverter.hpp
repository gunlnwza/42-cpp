#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <string>
# include <iostream>

typedef enum e_scalar_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
}	t_scalar_type;

typedef enum e_issue
{
	OK,
	ISSUE_OVERFLOW,
	ISSUE_UNDERFLOW,
}	t_issue;

typedef struct s_scalar_field
{
	char	c;
	int		i;
	float	f;
	double	d;

	t_issue	c_issue;
	t_issue	i_issue;
	t_issue	f_issue;
	t_issue	d_issue;
}	t_scalar_field;

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
