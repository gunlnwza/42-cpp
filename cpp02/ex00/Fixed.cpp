#include "Fixed.hpp"

// ---- ex00 -------------------------------------------------------------------

const int Fixed::nb_fractional_bits = 8;

Fixed::Fixed(void)
{
    std::cerr << "Default constructor called" << std::endl;
    this->raw = 0;
}

Fixed::Fixed(const Fixed &other)
{
    std::cerr << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed& Fixed::operator=(const Fixed &other)
{
    std::cerr << "Copy assignment operator called" << std::endl;
    this->raw = other.getRawBits();
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

// -----------------------------------------------------------------------------
