#include <iostream>
#include <algorithm>
#include <cmath>

#include "ISortStrategy.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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
    const int               max_compare_count = max_compare_count_formula(inputs.size());
    const std::string       name = strategy->get_name();
    const std::vector<int>  result = strategy->get_numbers();
    const int               compare_count = strategy->get_compare_count();
    const bool              unchanged = is_unchanged(inputs, result);
    const bool              sorted = is_sorted(result);

    std::cout << "[ Results Details ]" << std::endl;
    std::cout << name << " : " << "unchanged   = " << (unchanged ? "Yes" : "No") << std::endl;
    std::cout << name << " : " << "sorted      = " << (sorted ? "Yes" : "No") << std::endl;
    std::cout << name << " : " << "comparisons = " << compare_count << std::endl;
    if (unchanged && sorted && compare_count <= max_compare_count)
        std::cout << GREEN << name << " : OK (<= " << max_compare_count << " comparisons)" << RESET << std::endl;
    else
        std::cout << RED << name << " : KO (> " << max_compare_count << " comparisons)" << RESET << std::endl;
}
