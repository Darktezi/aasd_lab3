#include <iostream>
#include <vector>
#include <cstdlib>
#include <Windows.h>
#include <random>
#include <cmath>

#define SIZE 1000

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

template<typename Iterator>
Stats bubbleSort(Iterator begin, Iterator end) {
    Stats stats;
    bool swapped;

    for (auto i = begin; i != end; ++i) {
        swapped = false;

        for (auto j = begin; j != end - 1; ++j) {
            ++stats.comparison_count;
            if (*j > *(j + 1)) {
                std::iter_swap(j, j + 1);
                ++stats.copy_count;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    return stats;
}

template<typename Iterator>
Stats shellSort(Iterator begin, Iterator end) {
    Stats stats;
    auto n = std::distance(begin, end);

    for (auto gap = n / 2; gap > 0; gap /= 2) {
        for (auto i = begin + gap; i != end; ++i) {
            auto temp = *i;
            auto j = i;

            ++stats.copy_count;
            for (; j >= begin + gap && *(j - gap) > temp; j -= gap) {
                ++stats.comparison_count;
                *j = *(j - gap);
                ++stats.copy_count;
            }

            *j = temp;
        }
    }

    return stats;
}

template<typename Iterator>
Stats combSort(Iterator begin, Iterator end) {
    Stats stats;
    auto n = std::distance(begin, end);
    auto gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;

        if (gap < 1)
            gap = 1;

        swapped = false;

        for (auto i = begin; i != end - gap; ++i) {
            ++stats.comparison_count;
            if (*i > *(i + gap)) {
                std::iter_swap(i, i + gap);
                ++stats.copy_count;
                swapped = true;
            }
        }
    }

    return stats;
}

std::vector<int> generate_random_vector(size_t size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(rand() % 100);
    }
    return result;
}

std::vector<int> generate_sorted_vector(size_t size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(i);
    }
    return result;
}

std::vector<int> generate_inverted_vector(size_t size) {
    std::vector<int> result;
    for (int i = size - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {

    //Bubble sort for 100 random arrays, 1 sorted and 1 inverted 
    {
        std::cout << "size: " << SIZE << std::endl;
        std::cout << "===============================================================" << std::endl;
        std::cout << "Bubble sort for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            std::cout << "Number of array: " << i << std::endl;
            std::vector<int> arr = generate_random_vector(SIZE);
            Stats tmp = bubbleSort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = bubbleSort(sorted.begin(), sorted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = bubbleSort(inverted.begin(), inverted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }
    //Shell sort for 100 random arrays, 1 sorted and 1 inverted
    {
        std::cout << "===============================================================" << std::endl;
        std::cout << "Shell sort for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            std::vector<int> arr = generate_random_vector(SIZE);
            Stats tmp = shellSort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = shellSort(sorted.begin(), sorted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = shellSort(inverted.begin(), inverted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }
    //Comb sort for 100 random arrays, 1 sorted and 1 inverted
    {
        std::cout << "===============================================================" << std::endl;
        std::cout << "Comb sort for 100 random arrays, 1 sorted and 1 inverted" << std::endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            std::vector<int> arr = generate_random_vector(SIZE);
            Stats tmp = combSort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = combSort(sorted.begin(), sorted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = combSort(inverted.begin(), inverted.end());
        std::cout << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }
}