#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span
{
    private:
        unsigned int max_element_count;
        std::vector<int> vector;

    public:
        Span();
        Span(const Span& other);
        Span& operator=(const Span& other);
        ~Span();

        Span(unsigned int N);

        void addNumber(int num);

        unsigned int shortestSpan();
        unsigned int longestSpan();

        template <typename Iterator>
        void addNumbers(Iterator begin, Iterator end)
        {
            for (Iterator it = begin; it != end; ++it)
                this->addNumber(*it);
        }
};

#endif
