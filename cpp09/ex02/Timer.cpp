#include "Timer.hpp"

Timer::Timer()
{
    this->reset();
}

Timer::Timer(const Timer& other)
: t_start(other.t_start), t_stop(other.t_stop)
{}

Timer& Timer::operator=(const Timer& other)
{
    this->t_start = other.t_start;
    this->t_stop = other.t_stop;
    return (*this);
}

Timer::~Timer()
{}


void Timer::start()
{
    gettimeofday(&this->t_start, NULL);
}

void Timer::stop()
{
    gettimeofday(&this->t_stop, NULL);
}

long Timer::get_microseconds()
{
    int seconds;
    int microseconds;

    seconds = this->t_stop.tv_sec - this->t_start.tv_sec;
    microseconds = this->t_stop.tv_usec - this->t_start.tv_usec;
    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }
    return (1000000 * seconds + microseconds);
}

void Timer::reset()
{
    std::memset(&this->t_start, 0, sizeof(this->t_start));
    std::memset(&this->t_stop, 0, sizeof(this->t_stop));
}
