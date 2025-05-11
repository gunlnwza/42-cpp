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


static Token* make_token(const std::string& expression, size_t i)
{
    char c;

    c = expression[i];
    if (std::isdigit(c))
    {
        return (new Token(c - '0'));
    }
    switch (c)
    {
        case '+': return (new Token(ADD));
        case '-': return (new Token(SUB));
        case '*': return (new Token(MUL));
        case '/': return (new Token(DIV));
    }
    throw (std::runtime_error("unknown character"));
}

void RPN::tokenize(const std::string& expression)
{
    Token* token;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (std::isspace(expression[i]))
            continue ;
        token = make_token(expression, i);
        tokens.push(token);
    }
}

void RPN::process_current_token()
{
    Token* token;

    token = tokens.front();
    tokens.pop();
    if (token->get_type() == NUMBER)
    {
        // std::cout << "push " << *token << std::endl;;
        stack.push(token);
    }
    else
    {
        Token* left;
        Token* right;
        long result;

        left = stack.top();
        stack.pop();
        // std::cout << "pop " << *left << std::endl;;
        right = stack.top();
        // std::cout << "pop " << *right << std::endl;;
        stack.pop();
        switch (token->get_type())
        {
            case ADD:
                result = left->get_value() + right->get_value();
                break ;
            case SUB:
                result = left->get_value() - right->get_value();
                break ;
            case MUL:
                result = left->get_value() * right->get_value();
                break ;
            case DIV:
                result = left->get_value() / right->get_value();
                break ;
            default:
                throw (std::runtime_error("process_current_token: unknown operator"));
        }
        // std::cout << "push " << result << std::endl;
        stack.push(new Token(result));
        delete left;
        delete right;

        delete token;
    }
}

void RPN::evaluate(const std::string& expression)
{
    tokenize(expression);
    while (!tokens.empty())
        process_current_token();
    if (!stack.empty())
    {
        Token* result = stack.top();
        stack.pop();
        if (stack.empty())
        {
            std::cout << result->get_value() << std::endl;
            delete result;
        }
        else
            throw (std::runtime_error("evaluate: still have numbers in stack"));
        
    }
}
