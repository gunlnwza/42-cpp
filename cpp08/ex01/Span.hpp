#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span
{
	private:
		unsigned int		max_length;
		std::vector<int>	vector;

	public:
		Span(void);
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span(void);

		void	addNumber(int num);

		int	shortestSpan(void);
		int	longestSpan(void);
};

#endif
