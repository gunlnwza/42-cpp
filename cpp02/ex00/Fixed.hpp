#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
    public:
        // ---- ex00 -----------------------------------------------------------
        Fixed(void);
        Fixed(const Fixed &other);
        Fixed& operator=(const Fixed &other);
        ~Fixed(void);

        int  getRawBits(void) const;
        void setRawBits(int const raw);
        // ---------------------------------------------------------------------

    private:
        int              raw;
        static const int nb_fractional_bits;
};

#endif
