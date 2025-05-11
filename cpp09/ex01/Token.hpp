#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <iostream>

typedef enum e_token_type
{
    NONE,
    NUMBER,
    ADD,
    SUB,
    MUL,
    DIV
} t_token_type;

class Token
{
    private:
        t_token_type type;
        long value;

    public:
        Token();
        Token(const Token& other);
        Token& operator=(const Token& other);
        ~Token();

        Token(t_token_type type);
        Token(long value);

        t_token_type get_type() const;
        void set_type(t_token_type type);

        long get_value() const;
        void set_value(long value);

        Token operator+(const Token& other) const;
        Token operator-(const Token& other) const;
        Token operator*(const Token& other) const;
        Token operator/(const Token& other) const;
};

std::ostream& operator<<(std::ostream& os, Token& token);

#endif
