#ifndef SORTER_HPP
# define SORTER_HPP

# include <iostream>
# include <vector>
# include <sys/time.h>

# define MAX_NUM_TO_SHOW 10

class Sorter
{
    private:
        struct timeval t_start;
        struct timeval t_stop;

    public:
        Sorter();
        Sorter(const Sorter& other);
        Sorter& operator=(const Sorter& other);
        virtual ~Sorter() = 0;

        virtual void read_inputs(const std::vector<int>& inputs) = 0;
        
        virtual void sort() = 0;

        void time_start();
        void time_stop();
        long get_microseconds();
};

#endif
