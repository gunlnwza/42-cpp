#include <iostream>
#include "Fixed.hpp"

void subject_test(void)
{
    Fixed a;
    Fixed const b( 10 );
    Fixed const c( 42.42f );
    Fixed const d( b );

    a = Fixed( 1234.4321f );

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;
}

void small_increment_test(float start, float stop, float step)
{
    float value;
    int   raw;
    float diff;

    value = start;
    while (value < stop)
    {
        std::cout << "----------------------------------------" << std::endl;

        Fixed a(value);
        raw = a.getRawBits();
        diff = a.toFloat() - value;

        std::cout << "value  = " << value << std::endl;
        std::cout << "a->raw = " << raw << std::endl;
        std::cout << "(" << a.getRawBitsRepresentation() << ")" << std::endl;
        std::cout << "a      = " << a << std::endl;
        std::cout << "diff   = " << diff << std::endl;

        value += step;
    }
    std::cout << "----------------------------------------" << std::endl;
}

int main(void)
{
    // subject_test();
    small_increment_test(-1, 1, (float) 1 / 8);

    return (0);
}
