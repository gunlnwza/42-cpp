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


static char pop(std::queue<char>& queue)
{
    char    value;

    value = queue.front();
    queue.pop();
    return (value);
}

static long pop(std::stack<long>& stack)
{
    long    value;

    value = stack.top();
    stack.pop();
    return (value);
}


void RPN::tokenize(const std::string& expression)
{
    char    c;

    for (size_t i = 0; i < expression.length(); i++)
    {
        c = expression[i];
        if (std::isspace(c))
            continue ;
        if (std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/')
            tokens.push(c);
        else
            throw (std::runtime_error("tokenize: unknown character"));
    }
}

static long calculate_operation(long a, char op, long b)
{
    switch (op)
    {
        case '+': return (a + b);
        case '-': return (a - b);
        case '*': return (a * b);
        case '/':
            if (b == 0)
                throw (std::runtime_error("process_current_token: division by 0"));
            return (a / b);
        default: throw (std::runtime_error("process_current_token: unknown operator"));
    }
}

void RPN::process_current_token()
{
    char    token;
    long    left;
    long    right;
    long    result;

    token = pop(tokens);
    if (std::isdigit(token))
        stack.push(token - '0');
    else
    {
        if (stack.empty())
            throw (std::runtime_error("process_current_token: no num in stack for left num"));
        right = pop(stack);
        if (stack.empty())
            throw (std::runtime_error("process_current_token: no num in stack for right num"));
        left = pop(stack);
        result = calculate_operation(left, token, right);
        stack.push(result);
    }
}

void RPN::evaluate(const std::string& expression)
{
    long result;

    tokenize(expression);
    while (!tokens.empty())
        process_current_token();
    if (stack.empty())
        throw (std::runtime_error("evaluate: no result num"));
    result = pop(stack);
    if (!stack.empty())
        throw (std::runtime_error("evaluate: more than 1 result nums"));
    std::cout << result << std::endl;
}
