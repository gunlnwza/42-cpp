#ifndef FLAGTRAP_HPP
# define FLAGTRAP_HPP

# include "ClapTrap.hpp"

class FlagTrap: public ClapTrap
{
    public:
        FlagTrap(void);
        FlagTrap(const FlagTrap& other);
        FlagTrap& operator=(const FlagTrap& other);
        ~FlagTrap(void);

        FlagTrap(std::string name);

        void    highFiveGuys(void);
};

#endif
