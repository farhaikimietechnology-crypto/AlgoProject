#include <iostream>
using namespace std;

void showHomePage();
void showMenu();

int main() {
    int choice;

    showHomePage();

    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        showMenu();
    }
    else {
        cout << "\nExiting... Goodbye!\n";
    }

    return 0;
}

void showHomePage() {
    cout << "=============================\n";
    cout << "        STUDENT SYSTEM        \n";
    cout << "=============================\n";
    cout << "1. Go to Menu\n";
    cout << "2. Exit\n";
}

void showMenu() {
    int menuChoice;

    while (true) {
        cout << "\n=========== MAIN MENU ==========\n";
        cout << "1. Add Student Score\n";
        cout << "2. View Student Scores\n";
        cout << "3. Calculate Average Score\n";
        cout << "4. Back to Home\n";
        cout << "5. Exit Program\n";
        cout << "================================\n";
        cout << "Enter option: ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            cout << "\n>>> Add Student Score (Feature coming soon!)\n";
            break;
        case 2:
            cout << "\n>>> View Student Scores (Feature coming soon!)\n";
            break;
        case 3:
            cout << "\n>>> Calculate Average Score (Feature coming soon!)\n";
            break;
        case 4:
            cout << "\nReturning to Home Page...\n";
            return; // exit menu
        case 5:
            cout << "\nExiting System... Goodbye!\n";
            exit(0);
        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    }
}
