#include <iostream>
#include "Fixed.hpp"

// -------- ex00 --------

const int Fixed::nb_fractional_bits = 8;

Fixed::Fixed(void)
    : raw(0)
{
    std::cerr << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
    : raw(other.raw)
{
    std::cerr << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed &other)
{
    std::cerr << "Copy assignment operator called" << std::endl;
    this->raw = other.raw;
    return (*this);
}

Fixed::~Fixed(void)
{
    std::cerr << "Destructor called" << std::endl;
}

int  Fixed::getRawBits(void) const
{
    std::cerr << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int const raw)
{
    std::cerr << "setRawBits member function called" << std::endl;
    this->raw = raw;
}

// ******** ex01 ********

Fixed::Fixed(const int value)
{
    std::cerr << "Int constructor called" << std::endl;

    int raw = value << Fixed::nb_fractional_bits;

    // std::cerr << "********" << std::endl
    //           << "value=" << value << " ; raw=" << raw << std::endl
    //           << "********" << std::endl;

    this->raw = raw;
}

Fixed::Fixed(const float value)
{
    std::cerr << "Float constructor called" << std::endl;

    float temp = value * (1 << Fixed::nb_fractional_bits);
    int raw = temp;
    if (temp > int(temp)) // if <temp> got .5, then round <raw> up
        raw++;

    // std::cerr << "********" << std::endl
    //           << "value=" << value << " ; temp=" << temp << " ; raw=" << raw << std::endl
    //           << "********" << std::endl;

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
