#include <iostream>
#include <vector>
#include <cstdlib>
#include <Windows.h>

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

        if (!swapped) // Если не было перестановок на этой итерации, то массив уже отсортирован
            break;
    }

    return stats;
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {

    SetConsoleOutputCP(1251);
    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };

    std::cout << "Исходный массив: ";
    printArray(arr);

    Stats stats = bubbleSort(arr);

    std::cout << "Отсортированный массив: ";
    printArray(arr);

    std::cout << "Количество сравнений: " << stats.comparison_count << std::endl;
    std::cout << "Количество копирований: " << stats.copy_count << std::endl;

    return 0;
}