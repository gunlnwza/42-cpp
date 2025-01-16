#ifndef HARL_HPP
# define HARL_HPP

# include <string>

# define DEFAULT 0
# define DEBUG 1
# define INFO 2
# define WARNING 3
# define ERROR 4

class Harl
{
    public:
        void complain(int level);

    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);
};

#endif
