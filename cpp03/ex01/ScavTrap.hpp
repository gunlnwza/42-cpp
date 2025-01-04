#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
    public:
        ScavTrap(void);
        ScavTrap(const ScavTrap& other);
        ScavTrap& operator=(const ScavTrap& other);
        ~ScavTrap(void);

        ScavTrap(std::string name);

        void guardGate(void);

    private:
        std::string name;
        int         hit_point;
        int         energy_point;
        int         attack_damage;

        std::string type;
};

#endif
