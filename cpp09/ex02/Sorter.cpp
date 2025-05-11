#include "Sorter.hpp"


Sorter::Sorter()
{
    std::memset(&this->t_start, 0, sizeof(t_start));
    std::memset(&this->t_stop, 0, sizeof(t_stop));
}

Sorter::Sorter(const Sorter& other)
{
    *this = other;
}

Sorter& Sorter::operator=(const Sorter& other)
{
    this->t_start = other.t_start;
    this->t_stop = other.t_stop;
    return (*this);
}

Sorter::~Sorter()
{}


void Sorter::time_start()
{
    gettimeofday(&this->t_start, NULL);
}

void Sorter::time_stop()
{
    gettimeofday(&this->t_stop, NULL);
}

long Sorter::get_microseconds()
{
    int seconds;
    int microseconds;

    seconds = t_stop.tv_sec - t_start.tv_sec;
    microseconds = t_stop.tv_usec - t_start.tv_usec;
    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }
    return (1000 * seconds + microseconds / 1000);
}
