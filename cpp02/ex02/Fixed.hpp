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

        int  getRawBits(void) const;
        void setRawBits(int const raw);

        Fixed(const int value);
        Fixed(const float value);

        float toFloat(void) const;
        int   toInt(void) const;

        // ******** ex02 ********
        bool operator>(const Fixed &other) const;
        bool operator<(const Fixed &other) const;
        bool operator>=(const Fixed &other) const;
        bool operator<=(const Fixed &other) const;
        bool operator==(const Fixed &other) const;
        bool operator!=(const Fixed &other) const;

        Fixed operator+(const Fixed &other) const;
        Fixed operator-(const Fixed &other) const;
        Fixed operator*(const Fixed &other) const;
        Fixed operator/(const Fixed &other) const;

        Fixed& operator++();
        Fixed& operator--();
        Fixed operator++(int);
        Fixed operator--(int);

        static Fixed &min(Fixed &a, Fixed &b);
        static const Fixed &min(const Fixed &a, const Fixed &b);
        static Fixed &max(Fixed &a, Fixed &b);
        static const Fixed &max(const Fixed &a, const Fixed &b);

    private:
        int              raw;
        static const int nb_fractional_bits;
};

std::ostream& operator<<(std::ostream &os, const Fixed &fixed);

#endif
