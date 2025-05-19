#include "UserAccount.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
int main() {
<<<<<<< HEAD
    srand(time(0));
    int choice;
    cout << "1. Register\n2. Sign Up\nMake choice:  ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user, "users.txt");
        cout << "[✓] Successful login.\n";
        user.printInfo();
    }
    else if (choice == 2) {
        string uname, password;
        cout << "Input username: ";
        getline(cin, uname);
        cout << "Input password: ";
        getline(cin, password);

        if (!loginAndHandleFirstLogin(uname, password)) {
            cout << "[X] Wrong sign up.\n";
        }
        else {
            cout << "[X] Invalid selection.\n";
        }
        return 0;
    }
=======
        srand(time(0));
        int choice;
        cout << "1. Register\n2. Sign Up\nMake choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            UserAccount user = createUserfrominput();
            saveUsertofile(user, "users.txt");
            cout << "[✓] Successful login.\n";
            user.printInfo();
        }
        else if (choice == 2) {
            string uname, password;
            cout << "Input username: ";
            getline(cin, uname);
            cout << "Input password: ";
            getline(cin, password);

            if (!loginAndHandleFirstLogin(uname, password)) {
                cout << "[X] Wrong sign up.\n";
 } else {
        cout << "[X] Invalid selection.\n";
    }
    return 0;
}
>>>>>>> c3ec9aa8c2035839e1ed52b654d1db8cb3ff267f
