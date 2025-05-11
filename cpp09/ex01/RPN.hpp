#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <iostream>

# include <stack>
# include <queue>

class RPN
{
    private:
        std::queue<char> tokens;
        std::stack<long> stack;

        void tokenize(const std::string& expression);
        void process_current_token();

    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        void evaluate(const std::string& expression);
};

#endif
