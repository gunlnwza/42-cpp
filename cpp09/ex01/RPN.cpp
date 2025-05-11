#include "RPN.hpp"


RPN::RPN()
{}

RPN::RPN(const RPN& other)
{
    (void) other;
}

RPN& RPN::operator=(const RPN& other)
{
    (void) other;
    return (*this);
}

RPN::~RPN()
{}


void RPN::tokenize(const std::string& expression)
{
    Token token;
    char  c;

    for (size_t i = 0; i < expression.length(); i++)
    {
        c = expression[i];
        if (std::isspace(c))
            continue ;
        if (std::isdigit(c))
            token = Token(c - '0');
        else if (c == '+')
            token = Token(ADD);
        else if (c == '-')
            token = Token(SUB);
        else if (c == '*')
            token = Token(MUL);
        else if (c == '/')
            token = Token(DIV);
        else
            throw (std::runtime_error("tokenize: unknown char"));
        tokens.push(token);
    }
}

void RPN::process_current_token()
{
    Token token;

    token = tokens.front();
    tokens.pop();
    if (token.get_type() == NUMBER)
        stack.push(token);
    else
    {
        Token left;
        Token right;
        Token result;

        left = stack.top();
        stack.pop();
        right = stack.top();
        stack.pop();
        switch (token.get_type())
        {
            case ADD:
                result = left + right;
                break ;
            case SUB:
                result = left - right;
                break ;
            case MUL:
                result = left * right;
                break ;
            case DIV:
                result = left / right;
                break ;
            default:
                throw (std::runtime_error("process_current_token: unknown operator"));
        }

        stack.push(result);
    }
}

void RPN::evaluate(const std::string& expression)
{
    tokenize(expression);
    while (!tokens.empty())
        process_current_token();
    if (!stack.empty())
    {
        Token result = stack.top();
        stack.pop();
        if (stack.empty())
            std::cout << result << std::endl;
        else
            throw (std::runtime_error("evaluate: still have numbers in stack"));
    }
}
