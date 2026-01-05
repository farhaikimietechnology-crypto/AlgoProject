#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <string>
#include "sorting.h"
#include "searching.h"


using namespace std;
using namespace chrono;

const int MAX_STUDENTS = 10000;
Student students[MAX_STUDENTS];
int n = 0;

// ---------- FUNCTION PROTOTYPES ----------
void loadCSV();
void showHomePage();
void showMenu();
int safeStoi(const string& s);

// ---------- MAIN ----------
int main() {
    loadCSV();
    showHomePage();
    return 0;
}

// ---------- SAFE STRING TO INT ----------
int safeStoi(const string& s) {
    try {
        return stoi(s);
    }
    catch (...) {
        return 0; // default to 0 if conversion fails
    }
}

// ---------- LOAD CSV ----------
void loadCSV() {
    ifstream file("Student_performance_10k.csv");
    if (!file.is_open()) {
        cerr << "Error: Cannot open Student_performance_10k.csv\n";
        exit(1);
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line) && n < MAX_STUDENTS) {
        stringstream ss(line);
        string item;

        // Column A: Roll number
        getline(ss, item, ','); students[n].roll_no = item;

        // Column B: Gender
        getline(ss, item, ','); students[n].gender = item;

        // Column C: Race/Ethnicity
        getline(ss, item, ','); students[n].race_ethnicity = item;

        // Column D: Parental level
        getline(ss, item, ','); students[n].parental_level = item;

        // Column E: Lunch
        getline(ss, item, ','); students[n].lunch = safeStoi(item);

        // Column F: Test prep
        getline(ss, item, ','); students[n].test_prep = safeStoi(item);

        int total = 0;

        // Column G: Math
        getline(ss, item, ','); students[n].math_score = safeStoi(item); total += students[n].math_score;

        // Column H: Reading
        getline(ss, item, ','); students[n].reading_score = safeStoi(item); total += students[n].reading_score;

        // Column I: Writing
        getline(ss, item, ','); students[n].writing_score = safeStoi(item); total += students[n].writing_score;

        // Column J: Science
        getline(ss, item, ','); students[n].science_score = safeStoi(item); total += students[n].science_score;

        students[n].total_score = total;

        // Column K: Grade (convert 1/2/3 → C/B/A)
        getline(ss, item, ',');
        char gradeChar = 'F';
        if (!item.empty()) {
            switch (item[0]) {
            case '1': gradeChar = 'C'; break;
            case '2': gradeChar = 'B'; break;
            case '3': gradeChar = 'A'; break;
            default: gradeChar = 'F'; break;
            }
        }
        students[n].grade = gradeChar;

        n++;
    }

    file.close();
    cout << n << " students loaded successfully.\n";

    // Display first 100 UNSORTED data
    cout << "\nFirst 100 UNSORTED Data\n";
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
}

// ---------- HOME PAGE ----------
void showHomePage() {
    int choice;
    cout << "\n=============================\n";
    cout << "        STUDENT SYSTEM        \n";
    cout << "=============================\n";
    cout << "1. Go to Menu\n2. Exit\nEnter choice: ";
    cin >> choice;

    if (choice == 1) showMenu();
    else exit(0);
}

// ---------- MAIN MENU ----------
void showMenu() {
    int menuChoice;

    while (true) {
        cout << "\n=========== MAIN MENU ==========\n"
            << "1. Search Student\n"
            << "2. View Student Scores\n"
            << "3. Calculate Average Score\n"
            << "4. Back to Home\n"
            << "5. Exit Program\n"
            << "================================\n"
            << "Enter option: ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            showSearchMenu(students, n);
            break;

        case 2: {
            int sortChoice;
            while (true) {
                cout << "\n--- VIEW STUDENT SCORES ---\n"
                    << "1. Insertion Sort (Total Score & Grade)\n"
                    << "2. Quick Sort (Total Score & Grade)\n"
                    << "3. Back\n"
                    << "Enter option: ";
                cin >> sortChoice;

                if (sortChoice == 1) {
                    long long shiftCount = 0;
                    auto start = high_resolution_clock::now();
                    insertionSortByTotalScore(students, n, shiftCount);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);

                    cout << "\nSorted Student Scores (First 100)\n";
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

                    cout << "\nRuntime: " << duration.count() << " ms\n";
                    cout << "Total shifts: " << shiftCount << endl;
                }
                else if (sortChoice == 2) {
                    long long swapCount = 0;
                    auto start = high_resolution_clock::now();
                    quickSort(students, 0, n - 1, swapCount);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);

                    cout << "\nSorted Student Scores (First 100)\n";
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

                    cout << "\nRuntime: " << duration.count() << " ms\n";
                    cout << "Total swaps: " << swapCount << endl;
                }
                else if (sortChoice == 3) break;
                else cout << "Invalid choice!\n";
            }
            break;
        }

        case 3:
            cout << "\n>>> Calculate Average Score (Feature coming soon!)\n";
            break;

        case 4: return;

        case 5: exit(0);

        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    }
}
