#include <iostream>
#include <iomanip>
#include <sys/time.h>

#include <vector>
#include <deque>

#define NUM_TO_SHOW 10

// Containers used: std::vector, std::deque

void put_vector(const std::vector<int>& v, size_t n)
{
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if (n == 0)
        {
            std::cout << "[...]";
            break ;
        }
        std::cout << *it << " ";
        n--;
    }
}

void put_deque(const std::deque<int>& d, size_t n)
{
    for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
    {
        if (n == 0)
        {
            std::cout << "[...]";
            break ;
        }
        std::cout << *it << " ";
        n--;
    }
}

class Sorter
{
    private:
        struct timeval t_start;
        struct timeval t_stop;

    public:
        Sorter() {
            std::memset(&t_start, 0, sizeof(t_start));
            std::memset(&t_stop, 0, sizeof(t_stop));
        }
        Sorter(const Sorter& other) {
            *this = other;
        }
        Sorter& operator=(const Sorter& other) {
            this->t_start = other.t_start;
            this->t_stop = other.t_stop;
            return (*this);
        }
        virtual ~Sorter() = 0;

        virtual void read_input(const std::vector<int>& inputs) = 0;
        virtual void sort() = 0;

        void time_start() {
            gettimeofday(&this->t_start, NULL);
        }

        void time_stop() {
            gettimeofday(&this->t_stop, NULL);
        }

        long get_microseconds() {
            int seconds = t_stop.tv_sec - t_start.tv_sec;
            int microseconds = t_stop.tv_usec - t_start.tv_usec;

            if (microseconds < 0)
            {
                seconds--;
                microseconds += 1000000;
            }
            return (1000 * seconds + microseconds / 1000);
        }
};

class VectorSorter : public Sorter
{
    private:
        std::vector<int> vector;

    public:
        VectorSorter() {}
        VectorSorter(const VectorSorter& other) { *this = other; }
        VectorSorter& operator=(const VectorSorter& other) { this->vector = other.vector; return (*this); }
        ~VectorSorter() {}

        void read_input(const std::vector<int>& inputs) {
            this->vector = inputs;
        }

        void sort() {
            for (size_t i = 0; i < vector.size(); i++)
            {
                size_t min_index = i;
                for (size_t j = i + 1; j < vector.size(); j++)
                {
                    if (vector[j] < vector[min_index])
                        min_index = j;
                }
                if (min_index != i)
                    std::swap(vector[i], vector[min_index]);
            }
        }

        const std::vector<int> get_vector() const {
            return (this->vector);
        }
};

class DequeSorter : public Sorter
{
    private:
        std::deque<int> deque;

    public:
        DequeSorter() {}
        DequeSorter(const DequeSorter& other) { *this = other; }
        DequeSorter& operator=(const DequeSorter& other) { this->deque = other.deque; return (*this); }
        ~DequeSorter() {}

        void read_input(const std::vector<int>& inputs) {
            for (std::vector<int>::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
                this->deque.push_back(*it);
        }

        void sort() {
            for (size_t i = 0; i < deque.size(); i++) {
                size_t min_index = i;
                for (size_t j = i + 1; j < deque.size(); j++) {
                    if (deque[j] < deque[min_index])
                        min_index = j;
                }
                if (min_index != i)
                    std::swap(deque[i], deque[min_index]);
            }
        }

        const std::deque<int> get_deque() const {
            return (this->deque);
        }
};

int	main(int argc, char **argv)
{
    std::vector<int>    inputs;
    VectorSorter        vector_sorter;
    DequeSorter         deque_sorter;

    for (int i = 1; i < argc; i++)
    {
        int num = std::atoi(argv[i]);  // TODO: add range and number validations
        inputs.push_back(num);
    }

    vector_sorter.read_input(inputs);
    vector_sorter.time_start();
    vector_sorter.sort();
    vector_sorter.time_stop();

    deque_sorter.read_input(inputs);
    deque_sorter.time_start();
    deque_sorter.sort();
    deque_sorter.time_stop();

    std::cout << "Before: "; put_vector(inputs, NUM_TO_SHOW); std::cout << std::endl;
    std::cout << "After:  "; put_vector(vector_sorter.get_vector(), NUM_TO_SHOW); std::cout << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << "elements with std::vector : "
        << vector_sorter.get_microseconds() << "ms" << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << "elements with std::deque : "
        << vector_sorter.get_microseconds() << "ms" << std::endl;

    return (EXIT_SUCCESS);
}
