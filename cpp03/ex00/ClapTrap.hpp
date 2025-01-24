#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>
# include <ostream>

class ClapTrap
{
    public:
        ClapTrap(void);
        ClapTrap(const ClapTrap& other);
        ClapTrap& operator=(const ClapTrap& other);
        ~ClapTrap(void);

        ClapTrap(std::string name);

        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);

        std::string getName(void) const;
        void        setName(std::string name);

        int         getHitPoint(void) const;
        void        setHitPoint(int hit_point);

        int         getEnergyPoint(void) const;
        void        setEnergyPoint(int energy_point);

        int         getAttackDamage(void) const;
        void        setAttackDamage(int attack_damage);

    private:
        std::string name;
        int         hit_point;
        int         energy_point;
        int         attack_damage;
};

std::ostream& operator<<(std::ostream &os, ClapTrap &clap_trap);

#endif
