#ifndef SORTING_H
#define SORTING_H

#include <string>

struct Student {
    std::string roll_no;
    std::string gender;
    std::string race_ethnicity;
    std::string parental_level;
    int lunch;
    int test_prep;
    int math_score;
    int reading_score;
    int writing_score;
    int science_score;
    int total_score;
    std::string grade;
};

// Insertion Sort
void insertionSortByTotalScore(Student arr[], int size, long long& shiftCount);

// Quick Sort
void quickSort(Student arr[], int low, int high, long long& swapCount);

#endif
