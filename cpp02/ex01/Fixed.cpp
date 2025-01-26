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

// ---- ex01 -------------------------------------------------------------------

Fixed::Fixed(const int value)
{
    std::cerr << "Int constructor called" << std::endl;
    this->raw = value << Fixed::nb_fractional_bits;
}

Fixed::Fixed(const float value)
{
    std::cerr << "Float constructor called" << std::endl;

    float temp = value * (1 << Fixed::nb_fractional_bits);
    int raw = temp;
    // if (temp > int(temp)) // if <temp> got .5, then round <raw> up
    //     raw++;

    // std::cerr << "********" << std::endl
    //           << "value=" << value << " ; temp=" << temp << " ; raw=" << raw << std::endl
    //           << "********" << std::endl;

    this->raw = raw;
}

int Fixed::toInt(void) const
{
    return (this->raw >> Fixed::nb_fractional_bits);
}

float Fixed::toFloat(void) const
{
    float value = (float) this->raw / (float) (1 << Fixed::nb_fractional_bits);
    return (value);
}

// for debugging purposes
std::string Fixed::getRawBitsRepresentation(void) const
{
    std::string repr = "00000000000000000000000000000000";
    int         raw = this->raw;
    for (int i = 31; i >= 0; i--) { // Start from MSB (31st bit)
        if (raw & (1 << i)) {
            repr[31 - i] = '1';
        }
    }

    std::string repr_with_dot = repr.substr(0, 32 - Fixed::nb_fractional_bits) + "." + repr.substr(32 - Fixed::nb_fractional_bits, 32);    
    return (repr_with_dot);
}

std::ostream& operator<<(std::ostream &os, const Fixed &fixed)
{
    os << fixed.toFloat();
    return (os);
}

// -----------------------------------------------------------------------------
