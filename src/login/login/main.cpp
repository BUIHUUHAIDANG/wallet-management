#include "UserAccount.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {
    srand(time(0));
    int choice;
    cout << "1. Dang ky\n2. Dang nhap\nChon chuc nang: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user,"users.txt");
        cout << "[✓] Dang ky thanh cong!\n";
        user.printInfo();
    }
    else if (choice == 2) {
        string uname, password;
        cout << "Nhap username: ";
        getline(cin, uname);
        cout << "Nhap mat khau: ";
        getline(cin, password);

        if (!loginAndHandleFirstLogin(uname, password)) {
            cout << "[X] Sai thong tin dang nhap.\n";
        }
    }
    else {
        cout << "[X] Lua chon khong hop le.\n";
    }

    return 0;
}