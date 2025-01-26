#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
    public:
        ScavTrap(void);
        ScavTrap(const ScavTrap& other);
        ScavTrap& operator=(const ScavTrap& other);
        ~ScavTrap(void);

        ScavTrap(std::string name);

        void    guardGate(void);

        void    takeDamage(unsigned int amount);

        std::string getFullName(void) const;

    private:
        bool    is_gate_keeper_mode;
};

#endif
