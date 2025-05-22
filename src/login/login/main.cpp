
#include "UserAccount.h"
#include "Wallett.h"
#include <ctime>

#include <cstdlib>
#include <iostream>
int main() {
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
       
       
    }
    else {
            cout << "[X] Invalid selection.\n";
        }   
    return 0;
}

        


