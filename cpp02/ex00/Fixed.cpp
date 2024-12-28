#include <iostream>
#include "Fixed.hpp"

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
