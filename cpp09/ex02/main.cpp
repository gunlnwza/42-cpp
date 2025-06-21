#include <cmath>
#include <climits>
#include <algorithm>
#include <cerrno>

#include "vector_merge_insertion/VectorMergeInsertion.hpp"
#include "deque_merge_insertion/DequeMergeInsertion.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define PRINT_RESULTS_DETAILS true

// Containers used: std::vector, std::deque

static const std::vector<int> parse_inputs(int argc, char **argv)
{
    std::vector<int> inputs;
    char             *ptr;
    long             value;
    int              num;

    for (int i = 1; i < argc; i++)
    {
        errno = 0;
        value = std::strtol(argv[i], &ptr, 10);
        if (*ptr != '\0')
            throw (std::runtime_error("input have not-a-number"));
        if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
            throw (std::runtime_error("input have out-of-range number"));
        if (value <= 0)
            throw (std::runtime_error("input have non-positive number"));
        num = static_cast<int>(value);
        inputs.push_back(num);
    }
    return (inputs);
}

long get_microseconds(struct timeval t_start, struct timeval t_stop)
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
    return (1000000 * seconds + microseconds);
}

std::ostream& operator<<(std::ostream& os, const std::vector<int> v)
{
    const int max_head_length = 5;

    if (v.size() > max_head_length * 2)
    {
        for (size_t i = 0; i < max_head_length; ++i)
            std::cout << v[i] << " ";
        std::cout << "[...]";
        for (size_t i = v.size() - 5; i < v.size(); ++i)
            std::cout << " " << v[i];
    }
    else
    {
        for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        {
            if (it != v.begin())
                std::cout << " ";
            std::cout << *it;
        }
    }
    return (os);
}

bool is_unchanged(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> sorted_a = a;
    std::vector<int> sorted_b = b;

    std::sort(sorted_a.begin(), sorted_a.end());
    std::sort(sorted_b.begin(), sorted_b.end());
    return (sorted_a == sorted_b);
}

bool is_sorted(const std::vector<int>& v)
{
    if (v.size() == 0)
        return (true);
    for (size_t i = 0; i < v.size() - 1; ++i)
    {
        if (v[i] > v[i + 1])
            return (false);
    }
    return (true);
}

// https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91
int max_compare_count_formula(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

void print_result_details(const std::vector<int>& inputs, ISortStrategy* strategy)
{
    std::string         name;
    std::vector<int>    result;
    int                 compare_count;
    bool                sorted;
    bool                unchanged;

    name = strategy->get_name();
    result = strategy->get_numbers();
    compare_count = strategy->get_compare_count();
    unchanged = is_unchanged(inputs, result);
    sorted = is_sorted(result);
    
    std::cout << name << " : " << "unchanged = " << (unchanged ? "Yes" : "No") << std::endl;
    std::cout << name << " : " << "sorted = " << (sorted ? "Yes" : "No") << std::endl;
    std::cout << name << " : " << "compare_count = " << compare_count << std::endl;
    if (unchanged && sorted && compare_count <= max_compare_count_formula(inputs.size()))
        std::cout << GREEN << name << " : OK" << RESET << std::endl;
    else
        std::cout << RED << name << " : KO" << RESET << std::endl;
}

/*
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
*/
int	main(int argc, char** argv)
{
    std::vector<int> inputs;

    try {
        inputs = parse_inputs(argc, argv);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }

    VectorMergeInsertion vector_merge_insertion;
    DequeMergeInsertion  deque_merge_insertion;

    
    long            microseconds_vector;
    // long            microseconds_deque;

    std::vector<int> vector_result;
    // std::vector<int> deque_result;

    gettimeofday(&t_start, NULL);
    vector_merge_insertion.copy_numbers(inputs);
    vector_merge_insertion.sort();
    gettimeofday(&t_stop, NULL);
    microseconds_vector = get_microseconds(t_start, t_stop);
    vector_result = vector_merge_insertion.get_numbers();

    std::cout << "Before : " << inputs << std::endl;
    std::cout << "After  : " << vector_result << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << " elements with " << vector_merge_insertion.get_name() << " : " << microseconds_vector << " microseconds" << std::endl;

    // gettimeofday(&t_start, NULL);
    // deque_merge_insertion.copy_numbers(inputs);
    // deque_merge_insertion.sort();
    // gettimeofday(&t_stop, NULL);
    // microseconds_deque = get_microseconds(t_start, t_stop);
    // deque_result = deque_merge_insertion.get_numbers();

    // std::cout << "Time to process a range of " << n << " elements with " << deque_merge_insertion.get_name() << " : " << microseconds_deque << " microseconds" << std::endl;

    if (PRINT_RESULTS_DETAILS)
    {
        std::cout << std::endl;
        std::cout << "[ Results Details ]" << std::endl;
        std::cout << "max compare_count allowed = " << max_compare_count_formula(inputs.size()) << std::endl;
        std::cout << std::endl;
        print_result_details(inputs, &vector_merge_insertion);
        std::cout << std::endl;
        // print_result_details(inputs, &deque_merge_insertion);
    }

    return (EXIT_SUCCESS);
}
