#ifndef TIMER_HPP
# define TIMER_HPP

#include <sys/time.h>
#include <cstring>

class Timer
{
    private:
        struct timeval t_start;
        struct timeval t_stop;

    public:
        Timer();
        Timer(const Timer& other);
        Timer& operator=(const Timer& other);
        ~Timer();

        void start();
        void stop();
        long get_microseconds();
        void reset();
};

#endif
