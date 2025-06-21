#ifndef TIMER_HPP
# define TIMER_HPP

#include <sys/time.h>

class Timer
{
    private:
        struct timeval t_stop;
        struct timeval t_start;

    public:
        Timer();
        Timer(const Timer& other);
        Timer& operator=(const Timer& other);
        ~Timer();

        void time_start();
        void time_stop();
        long get_microseconds();
        void reset();
};

#endif
