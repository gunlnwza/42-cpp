#include "Token.hpp"


Token::Token()
: type(NONE), value(0)
{
    std::cout << "DC" << std::endl;
}

Token::Token(const Token& other)
{
    std::cout << "CC" << std::endl;
    *this = other;
}

Token& Token::operator=(const Token& other)
{
    std::cout << "CA" << std::endl;
    this->type = other.type;
    this->value = other.value;
    return (*this);
}

Token::~Token()
{
    std::cout << "D" << std::endl;
}


Token::Token(t_token_type type)
: type(type), value(0)
{
    std::cout << "C" << std::endl;
}

Token::Token(long value)
: type(NUMBER), value(value)
{
    std::cout << "C" << std::endl;
}


t_token_type Token::get_type() const
{
    return (this->type);
}

void Token::set_type(t_token_type type)
{
    this->type = type;
}


long Token::get_value() const
{
    return (this->value);
}

void Token::set_value(long value)
{
    this->value = value;
}


Token Token::operator+(const Token& other) const
{
    return (Token(this->value + other.value));
}

Token Token::operator-(const Token& other) const
{
    return (Token(this->value - other.value));
}

Token Token::operator*(const Token& other) const
{
    return (Token(this->value * other.value));
}

Token Token::operator/(const Token& other) const
{
    return (Token(this->value / other.value));
}


std::ostream& operator<<(std::ostream& os, Token& token)
{
    switch (token.get_type())
    {
        case NUMBER:
            std::cout << token.get_value();
            break ;
        case ADD:
            std::cout << "+";
            break ;
        case SUB:
            std::cout << "-";
            break ;
        case MUL:
            std::cout << "*";
            break ;
        case DIV:
            std::cout << "/";
            break ;
        default:
            throw (std::runtime_error("operator<<: unknown token's type"));
    }
    return (os);
}
