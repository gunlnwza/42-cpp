#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"


class Form
{
	private:
		const std::string	name;
		bool				isSigned;
		const int			gradeToSign;
		const int			gradeToExecute;

		static void	assertValidGrade(int grade);

	public:
		Form(void);
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form(void);

		Form(const std::string& name, int gradeToSign, int gradeToExecute);

		std::string	getName(void) const;
		bool		getIsSigned(void) const;
		int			getGradeToSign(void) const;
		int			getGradeToExecute(void) const;

		void	beSigned(Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char*	what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const Form& form);

#endif
