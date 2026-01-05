#include <iostream>
#include <iomanip>
#include <string>
#include "sorting.h" 

using namespace std;

extern Student students[];
extern int n;


void displayUnsortedData() {
    if (n == 0) {
        cout << "\n[Error] No data loaded. Please restart the program.\n";
        return;
    }

    cout << "\n========== FIRST 100 UNSORTED RECORDS ==========\n";
    cout << left
        << setw(8) << "RollNo"
        << setw(8) << "Gender"
        << setw(15) << "Race"
        << setw(20) << "Parental Level"
        << setw(8) << "Lunch"
        << setw(12) << "TestPrep"
        << setw(8) << "Math"
        << setw(8) << "Reading"
        << setw(8) << "Writing"
        << setw(8) << "Science"
        << setw(10) << "Total"
        << setw(6) << "Grade\n";

    cout << string(125, '-') << "\n";

    for (int i = 0; i < 100 && i < n; i++) {
        cout << left
            << setw(8) << students[i].roll_no
            << setw(8) << students[i].gender
            << setw(15) << students[i].race_ethnicity
            << setw(20) << students[i].parental_level
            << setw(8) << students[i].lunch
            << setw(12) << students[i].test_prep
            << setw(8) << students[i].math_score
            << setw(8) << students[i].reading_score
            << setw(8) << students[i].writing_score
            << setw(8) << students[i].science_score
            << setw(10) << students[i].total_score
            << setw(6) << students[i].grade
            << "\n";
    }
    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}