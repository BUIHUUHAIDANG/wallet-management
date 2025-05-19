#include "UserAccount.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
int main() {                    
    srand(time(0));
    int choice;
    cout << "1. Register\n2. Sign In\nMake choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user, "users.txt");
        cout << "[✓] Tạo tài khoản thành công.\n";
        user.printInfo();
    } else if (choice == 2) {
        string uname, password;
        cout << "Input username: ";
        getline(cin, uname);
        cout << "Input password: ";
        getline(cin, password);
        if (!loginAndHandleFirstLogin(uname, password)) {
            cout << "[X] Sai thông tin đăng nhập.\n";
        } else {
            ifstream inFile("users.txt");
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string _uname, fullname, phone, pw, wallet;
                bool isManager, firstLogin;
                getline(ss, _uname, ',');
                getline(ss, fullname, ',');
                getline(ss, phone, ',');
                getline(ss, pw, ',');
                getline(ss, wallet, ',');
                ss >> isManager;
                ss.ignore();
                ss >> firstLogin;
                if (_uname == uname) {
                    if (isManager)
                        showAdminMenu();
                    else
                        showUserMenu(uname);
                    break;
                }
            }
            inFile.close();
        }
    } else {
        cout << "[X] Invalid selection.\n";
    }
    return 0;
}
