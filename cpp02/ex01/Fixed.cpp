#include <iostream>
#include "Fixed.hpp"

const int Fixed::nb_fractional_bits = 8;

Fixed::Fixed(void)
    : raw(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
    : raw(other.raw)
{
    std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    this->raw = other.raw;
    return (*this);
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

int  Fixed::getRawBits(void)
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->raw = raw;
}


Fixed::Fixed(const int value)
{
    this->raw = value << Fixed::nb_fractional_bits;
}

Fixed::Fixed(const float value)//TODO
{
    this->raw = value;
}

float Fixed::toFloat(void)//TODO
{
    return (this->raw);
}

int Fixed::toInt(void) const
{
    int value = this->raw >> nb_fractional_bits;
    return (value);
}

std::ostream& operator<<(std::ostream &os, const Fixed &fixed)//TODO
{
    os << fixed.toInt();
    return (os);
}
