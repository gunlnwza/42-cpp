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
    int raw = value << Fixed::nb_fractional_bits;
    this->setRawBits(raw);
}

Fixed::Fixed(const float value)
{
    int raw = value * (1 << Fixed::nb_fractional_bits);
    this->setRawBits(raw);
}

float Fixed::toFloat(void)
{
    ((float) this->getRawBits() / (float)(1 << Fixed::nb_fractional_bits));
}

int Fixed::toInt(void) const
{
    int value = this->raw >> Fixed::nb_fractional_bits;
    return (value);
}

std::ostream& operator<<(std::ostream &os, const Fixed &fixed)
{
    os << ((Fixed) fixed).toFloat();
    return (os);
}
