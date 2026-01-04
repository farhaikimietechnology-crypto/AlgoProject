#include <iostream>
#include <iomanip>
#include <string>
#include "sorting.h" 

using namespace std;

extern Student students[];
extern int n;

void generatePerformanceReport() {
    string names[] = { "Math", "Reading", "Writing", "Science" };
    int mins[4] = { 101, 101, 101, 101 };
    int maxs[4] = { -1, -1, -1, -1 };
    double sums[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < n; i++) {
        int scores[] = { students[i].math_score, students[i].reading_score,
                         students[i].writing_score, students[i].science_score };

        for (int j = 0; j < 4; j++) {
            if (scores[j] < mins[j]) mins[j] = scores[j];
            if (scores[j] > maxs[j]) maxs[j] = scores[j];
            sums[j] += scores[j];
        }
    }

    cout << "\n" << string(55, '=') << endl;
    cout << "          SUBJECT PERFORMANCE STATISTICS REPORT          " << endl;
    cout << string(55, '=') << endl;
    cout << left << setw(15) << "Subject" << setw(10) << "Min" << setw(10) << "Max" << setw(10) << "Average" << endl;
    cout << string(55, '-') << endl;

    double highestAvg = -1, lowestAvg = 101;
    string bestSub, worstSub;

    for (int i = 0; i < 4; i++) {
        double avg = (n > 0) ? (sums[i] / n) : 0; 
        cout << left << setw(15) << names[i]
            << setw(10) << mins[i]
            << setw(10) << maxs[i]
            << fixed << setprecision(2) << setw(10) << avg << endl;

        if (avg > highestAvg) { highestAvg = avg; bestSub = names[i]; }
        if (avg < lowestAvg) { lowestAvg = avg; worstSub = names[i]; }
    }

    cout << string(55, '-') << endl;
    cout << "Highest Performing Subject: " << bestSub << " (" << highestAvg << ")\n";
    cout << "Lowest Performing Subject:  " << worstSub << " (" << lowestAvg << ")\n";
}

   