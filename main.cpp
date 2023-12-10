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

Stats bubbleSort(std::vector<int>& arr) {
    Stats stats;
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            ++stats.comparison_count;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                ++stats.copy_count;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    return stats;
}

Stats shellSort(std::vector<int>& arr) {
    Stats stats;
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;

            ++stats.copy_count;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                ++stats.comparison_count;
                arr[j] = arr[j - gap];
                ++stats.copy_count;
            }

            arr[j] = temp;
        }
    }

    return stats;
}

Stats combSort(std::vector<int>& arr) {
    Stats stats;
    int n = arr.size();
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;

        if (gap < 1)
            gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            ++stats.comparison_count;
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
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
            //cout << "Number of array: " << i << endl;
            std::vector<int> arr = generate_random_vector(SIZE);
            Stats tmp = bubbleSort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = bubbleSort(sorted);
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = bubbleSort(inverted);
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
            Stats tmp = shellSort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = shellSort(sorted);
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = shellSort(inverted);
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
            Stats tmp = combSort(arr);
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        std::cout << std::endl;
        std::cout << "Average comparison quantity: " << sum_comparison / 100 << std::endl;
        std::cout << "Average copy quantity: " << sum_copy / 100 << std::endl;

        std::vector<int> sorted = generate_sorted_vector(SIZE);
        Stats sorted_stats = combSort(sorted);
        std::cout << std::endl;
        std::cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << std::endl;

        std::vector<int> inverted = generate_inverted_vector(SIZE);
        Stats inverted_stats = combSort(inverted);
        std::cout << std::endl;
        std::cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << std::endl;
        std::cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << std::endl;
    }
}