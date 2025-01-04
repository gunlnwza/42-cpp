#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
    public:
        // -------- ex00 --------
        Fixed(void);
        Fixed(const Fixed &other);
        Fixed& operator=(const Fixed &other);
        ~Fixed(void);

        int  getRawBits(void) const;
        void setRawBits(int const raw);

        // ******** ex01 ********
        Fixed(const int value);
        Fixed(const float value);

        float toFloat(void) const;
        int   toInt(void) const;

    private:
        int              raw;
        static const int nb_fractional_bits;
};

// ******** ex01 ********
std::ostream& operator<<(std::ostream &os, const Fixed &fixed);

#endif
