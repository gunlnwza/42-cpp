#ifndef RPN_HPP
# define RPN_HPP

# include <string>

# include <stack>
# include <queue>

# include "Token.hpp"

class RPN
{
    private:
        std::queue<Token> tokens;
        std::stack<Token> stack;

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
