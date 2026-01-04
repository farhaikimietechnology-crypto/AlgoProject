#include "sorting.h"
#include <utility>   // for std::swap

// =======================================================
// INSERTION SORT
// Sort by: total_score DESC, grade ASC
// =======================================================
void insertionSortByTotalScore(Student arr[], int n, long long& shiftCount) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0 &&
            (arr[j].total_score < key.total_score ||
                (arr[j].total_score == key.total_score &&
                    arr[j].grade > key.grade))) {

            arr[j + 1] = arr[j];
            shiftCount++;
            j--;
        }
        arr[j + 1] = key;
    }
}

// =======================================================
// QUICK SORT (Helper comparison)
// Sort by: total_score DESC, grade ASC
// =======================================================
bool lessThan(const Student& a, const Student& b) {
    if (a.total_score != b.total_score)
        return a.total_score > b.total_score;   // DESC
    return a.grade < b.grade;                   // ASC
}

// =======================================================
// PARTITION FUNCTION
// =======================================================
int partition(Student arr[], int low, int high, long long& swapCount) {
    Student pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (lessThan(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
            swapCount++;
        }
    }

    std::swap(arr[i + 1], arr[high]);
    swapCount++;

    return i + 1;
}

// =======================================================
// QUICK SORT
// =======================================================
void quickSort(Student arr[], int low, int high, long long& swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}
