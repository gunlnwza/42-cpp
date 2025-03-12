#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"

class AForm
{
	private:
		const std::string	name;
		bool				isSigned;
		const int			gradeToSign;
		const int			gradeToExecute;

		static void	assertValidGrade(int grade);

	public:
		AForm(void);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm(void) = 0;

		AForm(const std::string& name, int gradeToSign, int gradeToExecute);

		std::string	getName(void) const;
		bool		getIsSigned(void) const;
		int			getGradeToSign(void) const;
		int			getGradeToExecute(void) const;

		void			beSigned(Bureaucrat& bureaucrat);
		virtual void	execute(Bureaucrat const & executor) const;

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

		class FormNotSignedException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const AForm& form);

#endif
