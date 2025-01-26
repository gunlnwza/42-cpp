#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>
# include <iostream>

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

        void putNoHitPointMessage(std::string additional_message);
        void putNoEnergyPointMessage(std::string additional_message);

        std::string getName(void) const;
        void        setName(std::string name);
        std::string getFullName(void) const;

        int         getHitPoint(void) const;
        void        setHitPoint(int hit_point);

        int         getEnergyPoint(void) const;
        void        setEnergyPoint(int energy_point);

        int         getAttackDamage(void) const;
        void        setAttackDamage(int attack_damage);

        std::string getTypeName(void) const;
        void        setTypeName(std::string type_name);

    private:
        std::string name;
        int         hit_point;
        int         energy_point;
        int         attack_damage;

        std::string type_name;  // for using in member functions only
};

std::ostream& operator<<(std::ostream &os, ClapTrap &clap_trap);

#endif
