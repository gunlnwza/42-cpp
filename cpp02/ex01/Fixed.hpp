#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
    public:
        Fixed(void);
        Fixed(const Fixed &other);
        Fixed& operator=(const Fixed &other);
        ~Fixed(void);

        int  getRawBits(void);
        void setRawBits(int const raw);

        Fixed(const int value);
        Fixed(const float value);

        float toFloat(void);
        int   toInt(void) const;

        std::ostream& operator<<(std::ostream &os, const Fixed &fixed);

    private:
        int              raw;
        static const int nb_fractional_bits;
};

#endif
