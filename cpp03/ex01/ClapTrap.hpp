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
        int         getHitPoint(void) const;
        int         getEnergyPoint(void) const;
        int         getAttackDamage(void) const;
        std::string getType(void) const;

        void        setName(std::string name);
        void        setHitPoint(int hit_point);
        void        setEnergyPoint(int energy_point);
        void        setAttackDamage(int attack_damage);
        void        setType(std::string type);

    private:
        std::string name;
        int         hit_point;
        int         energy_point;
        int         attack_damage;

        std::string type;
};

std::ostream& operator<<(std::ostream &os, ClapTrap &trap);

#endif
