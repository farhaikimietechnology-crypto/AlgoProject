#include <iostream>
#include <iomanip>
#include <string>
#include "sorting.h" 

using namespace std;

extern Student students[];
extern int n;

void analyzeAtRiskStudents() {
    const int PASSING_MARK = 40;
    int failCount = 0;
    int displayedCount = 0;

    cout << "\n" << string(70, '=') << endl;
    cout << "           AT RISK STUDENT DETAILS (First 100)           " << endl;
    cout << string(70, '=') << endl;
    cout << left << setw(10) << "Roll No"
        << setw(15) << "Math"
        << setw(15) << "Reading"
        << setw(15) << "Writing"
        << "Science" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < n; i++) {
        bool isAtRisk = (students[i].math_score < PASSING_MARK ||
            students[i].reading_score < PASSING_MARK ||
            students[i].writing_score < PASSING_MARK ||
            students[i].science_score < PASSING_MARK);

        if (isAtRisk) {
            failCount++;

            if (displayedCount < 100) {
                cout << left << setw(10) << students[i].roll_no;

                if (students[i].math_score < PASSING_MARK)
                    cout << "\033[31m" << setw(15) << ("Math: " + to_string(students[i].math_score)) << "\033[0m";
                else
                    cout << setw(15) << ("Math: " + to_string(students[i].math_score));

                if (students[i].reading_score < PASSING_MARK)
                    cout << "\033[31m" << setw(15) << ("Reading: " + to_string(students[i].reading_score)) << "\033[0m";
                else
                    cout << setw(15) << ("Reading: " + to_string(students[i].reading_score));

                if (students[i].writing_score < PASSING_MARK)
                    cout << "\033[31m" << setw(15) << ("Writing: " + to_string(students[i].writing_score)) << "\033[0m";
                else
                    cout << setw(15) << ("Writing: " + to_string(students[i].writing_score));

                if (students[i].science_score < PASSING_MARK)
                    cout << "\033[31m" << ("Science: " + to_string(students[i].science_score)) << "\033[0m" << endl;
                else
                    cout << ("Science: " + to_string(students[i].science_score)) << endl;

                displayedCount++;
            }
        }
    }

    double percentage = (n > 0) ? ((double)failCount / n * 100) : 0;

    cout << string(70, '-') << endl;
    cout << "Total Students Scanned: " << n << endl;
    cout << "Students failing >= 1 subject: " << failCount << endl;
    cout << "Risk Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;

    if (percentage > 10.0) {
        cout << "Status: \033[31mURGENT - High deficiency detected.\033[0m\n";
    }
    else {
        cout << "Status: STABLE\n";
    }

    cout << "\nPress Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}