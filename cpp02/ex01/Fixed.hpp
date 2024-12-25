#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
    public:
        Fixed(void);
        Fixed(const Fixed &other);
        Fixed& operator=(const Fixed &other);
        ~Fixed(void);

        Fixed(const int value);
        Fixed(const float value);

        int  getRawBits(void);
        void setRawBits(int const raw);



    private:
        int              raw;
        static const int nb_fractional_bits;
};

#endif
