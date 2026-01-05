#include "searching.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

// Convert string to lowercase
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Compare both search algorithms
void compareSearches(Student students[], int count) {
    cout << "\n--- SEARCH STUDENT ---\n";
    cout << "Enter Roll Number to search: ";
    string searchRoll, searchGrade;
    cin >> searchRoll;
    cout << "Enter Grade to search (A/B/C/F): ";
    cin >> searchGrade;

    string targetRoll = toLowerCase(searchRoll);
    char targetGradeChar = toupper(searchGrade[0]);

    cout << "\nSearching for Roll: " << searchRoll << " with Grade: " << targetGradeChar << "...\n";
    cout << "==========================================\n";
    cout << "RUNNING BOTH SEARCH ALGORITHMS...\n\n";

    // Store the original students array
    Student* originalStudents = new Student[count];
    for (int i = 0; i < count; i++) {
        originalStudents[i] = students[i];
    }

    // --- LINEAR SEARCH ---
    cout << "1. LINEAR SEARCH RESULTS:\n";
    cout << "--------------------------\n";

    bool linearFound = false;
    int linearComparisons = 0;
    int linearFoundIndex = -1;
    auto linearStart = high_resolution_clock::now();

    for (int i = 0; i < count; i++) {
        linearComparisons++;
        if (toLowerCase(originalStudents[i].roll_no) == targetRoll &&
            !originalStudents[i].grade.empty() && toupper(originalStudents[i].grade[0]) == targetGradeChar) {
            linearFound = true;
            linearFoundIndex = i;
            break;
        }
    }

    auto linearStop = high_resolution_clock::now();
    auto linearDuration = duration_cast<microseconds>(linearStop - linearStart);

    if (linearFound) {
        cout << "!STUDENT FOUND!\n";
        cout << "Search Time: " << linearDuration.count() << " microseconds\n";
        cout << "Comparisons: " << linearComparisons << "\n";
    }
    else {
        cout << "!!!STUDENT NOT FOUND!!!\n";
        cout << "Search Time: " << linearDuration.count() << " microseconds\n";
        cout << "Comparisons: " << linearComparisons << "\n";
    }

    // --- BINARY SEARCH ---
    cout << "\n2. BINARY SEARCH RESULTS:\n";
    cout << "--------------------------\n";

    // Create sorted copy for binary search (pre-sorted once for comparison)
    Student* sortedStudents = new Student[count];
    for (int i = 0; i < count; i++) {
        sortedStudents[i] = students[i];
    }

    // Sort once before timing (simulating pre-sorted data)
    sort(sortedStudents, sortedStudents + count, [](const Student& a, const Student& b) {
        return a.roll_no < b.roll_no;
        });

    // Now measure ONLY the search time (assuming data is already sorted)
    bool binaryFound = false;
    int binaryComparisons = 0;
    int binaryFoundIndex = -1;
    auto binaryStart = high_resolution_clock::now();

    int low = 0, high = count - 1;
    while (low <= high) {
        binaryComparisons++;
        int mid = low + (high - low) / 2;

        string currentRoll = toLowerCase(sortedStudents[mid].roll_no);
        char currentGrade = !sortedStudents[mid].grade.empty() ? toupper(sortedStudents[mid].grade[0]) : '\0';

        if (currentRoll == targetRoll && currentGrade == targetGradeChar) {
            binaryFound = true;
            binaryFoundIndex = mid;
            break;
        }
        else if (currentRoll < targetRoll || (currentRoll == targetRoll && currentGrade < targetGradeChar)) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    auto binaryStop = high_resolution_clock::now();
    auto binaryDuration = duration_cast<microseconds>(binaryStop - binaryStart);

    if (binaryFound) {
        cout << "!STUDENT FOUND!\n";
        cout << "Search Time: " << binaryDuration.count() << " microseconds\n";
        cout << "Comparisons: " << binaryComparisons << "\n";
    }
    else {
        cout << "!!!STUDENT NOT FOUND!!!\n";
        cout << "Search Time: " << binaryDuration.count() << " microseconds\n";
        cout << "Comparisons: " << binaryComparisons << "\n";
    }

    // --- DISPLAY STUDENT DETAILS IF FOUND ---
    if (linearFound || binaryFound) {
        cout << "\n==========================================\n";
        cout << "STUDENT DETAILS:\n";
        cout << "==========================================\n";

        Student* studentToShow = linearFound ? &originalStudents[linearFoundIndex] : &sortedStudents[binaryFoundIndex];
        cout << left
            << setw(20) << "Roll Number: " << studentToShow->roll_no << "\n"
            << setw(20) << "Gender: " << studentToShow->gender << "\n"
            << setw(20) << "Race/Ethnicity: " << studentToShow->race_ethnicity << "\n"
            << setw(20) << "Parental Level: " << studentToShow->parental_level << "\n"
            << setw(20) << "Math Score: " << studentToShow->math_score << "\n"
            << setw(20) << "Reading Score: " << studentToShow->reading_score << "\n"
            << setw(20) << "Writing Score: " << studentToShow->writing_score << "\n"
            << setw(20) << "Science Score: " << studentToShow->science_score << "\n"
            << setw(20) << "Total Score: " << studentToShow->total_score << "\n"
            << setw(20) << "Grade: " << studentToShow->grade << "\n";
    }

    // --- COMPARISON SUMMARY ---
    cout << "\n==========================================\n";
    cout << "SEARCH TIME COMPARISON:\n";
    cout << "==========================================\n";
    cout << left << setw(25) << "Algorithm:" << setw(20) << "Search Time" << setw(15) << "Comparisons" << "\n";
    cout << string(60, '-') << "\n";
    cout << left << setw(25) << "Linear Search:"
        << setw(20) << (to_string(linearDuration.count()) + " microseconds")
        << setw(15) << linearComparisons << "\n";
    cout << left << setw(25) << "Binary Search:"
        << setw(20) << (to_string(binaryDuration.count()) + " microseconds")
        << setw(15) << binaryComparisons << "\n";

    cout << "\n==========================================\n";
    cout << "CONCLUSION:\n";
    cout << "==========================================\n";

    if (linearDuration.count() < binaryDuration.count()) {
        cout << "LINEAR SEARCH was faster.\n";
        cout << "  - Faster by: " << (binaryDuration.count() - linearDuration.count()) << " microseconds\n";
    }
    else {
        cout << "BINARY SEARCH was faster.\n";
        cout << "  - Faster by: " << (linearDuration.count() - binaryDuration.count()) << " microseconds\n";
    }
    cout << "==========================================\n";

    delete[] originalStudents;
    delete[] sortedStudents;
}

// Search Menu
void showSearchMenu(Student students[], int count) {
    int searchChoice;

    while (true) {
        cout << "\n--- SEARCH STUDENT ---\n"
            << "1. Search (Roll Number and Grade)\n"
            << "2. Back\n"
            << "Enter option: ";
        cin >> searchChoice;

        switch (searchChoice) {
        case 1:
            compareSearches(students, count);
            break;

        case 2:
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}