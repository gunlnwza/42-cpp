#include "Fixed.hpp"

#define DEBUG false

// -------- ex00 --------

const int Fixed::nb_fractional_bits = 8;

Fixed::Fixed(void)
    : raw(0)
{
    if (DEBUG)
        std::cerr << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
    : raw(other.raw)
{
    if (DEBUG)
        std::cerr << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed &other)
{
    if (DEBUG)
        std::cerr << "Copy assignment operator called" << std::endl;
    
    this->raw = other.raw;
    return (*this);
}

Fixed::~Fixed(void)
{
    if (DEBUG)
        std::cerr << "Destructor called" << std::endl;
}

int  Fixed::getRawBits(void) const
{
    if (DEBUG)
        std::cerr << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int const raw)
{
    if (DEBUG)
        std::cerr << "setRawBits member function called" << std::endl;
    this->raw = raw;
}

// ******** ex01 ********

Fixed::Fixed(const int value)
{
    int raw = value << Fixed::nb_fractional_bits;
    if (DEBUG)
    {
        std::cerr << "Int constructor called" << std::endl;
        std::cerr << "********" << std::endl
                  << "value=" << value << " ; raw=" << raw << std::endl
                  << "********" << std::endl;
    }
    this->raw = raw;
}

Fixed::Fixed(const float value)
{

    float temp = value * (1 << Fixed::nb_fractional_bits);
    int raw = temp;
    if (temp > int(temp)) // if <temp> got .5, then round <raw> up
        raw++;
    if (DEBUG)
    {
        std::cerr << "Float constructor called" << std::endl;
        std::cerr << "********" << std::endl
                << "value=" << value << " ; temp=" << temp << " ; raw=" << raw << std::endl
                << "********" << std::endl;
    }
    this->raw = raw;
}

int Fixed::toInt(void) const
{
    int value = this->raw >> Fixed::nb_fractional_bits;
    return (value);
}

float Fixed::toFloat(void) const
{
    float value = (float) this->raw / (float) (1 << Fixed::nb_fractional_bits);
    return (value);
}

std::ostream& operator<<(std::ostream &os, const Fixed &fixed)
{
    os << fixed.toFloat();
    return (os);
}

// ******** ex02 ********

bool Fixed::operator>(const Fixed &other) const
{
    return (this->raw > other.raw);
}

bool Fixed::operator<(const Fixed &other) const
{
    return (this->raw < other.raw);
}

bool Fixed::operator>=(const Fixed &other) const
{
    return (this->raw >= other.raw);
}

bool Fixed::operator<=(const Fixed &other) const
{
    return (this->raw <= other.raw);
}

bool Fixed::operator==(const Fixed &other) const
{
    return (this->raw == other.raw);
}

bool Fixed::operator!=(const Fixed &other) const
{
    return (this->raw != other.raw);
}


Fixed Fixed::operator+(const Fixed &other) const
{
    return (Fixed(this->toFloat() + other.toFloat()));
}

Fixed Fixed::operator-(const Fixed &other) const
{
    return (Fixed(this->toFloat() - other.toFloat()));
}

Fixed Fixed::operator*(const Fixed &other) const
{
    return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed Fixed::operator/(const Fixed &other) const
{
    return (Fixed(this->toFloat() / other.toFloat()));
}


Fixed& Fixed::operator++()
{
    this->raw++;
    return (*this);
}

Fixed& Fixed::operator--()
{
    this->raw--;
    return (*this);
}

Fixed Fixed::operator++(int)
{
    Fixed prev = *this;
    this->raw++;
    return (prev);
}

Fixed Fixed::operator--(int)
{
    Fixed prev = *this;
    this->raw--;
    return (prev);
}


Fixed& Fixed::min(Fixed &a, Fixed &b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

Fixed& Fixed::max(Fixed &a, Fixed &b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b)
{
    if (a > b)
        return (a);
    else
        return (b);
}
