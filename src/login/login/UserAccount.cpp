#include "UserAccount.h"
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>




UserAccount::UserAccount(const string& uname, const string& name, const string& phone, bool manager) {
	username = uname;
	fullname = name;
	phonenumber = phone;
	isManager = manager;
	firstlogin = true;
	WalletID = "WalletID_" + uname;
}
void UserAccount::setPassword(const string& pw) {
	passwordHash = pw;

}
void UserAccount::setFirstLogin(bool status) {
	firstlogin = status;
}
string UserAccount::getUsername() const {
	return username;
}
string UserAccount::getPasswordHash() const { 
	return passwordHash;
}
	
string UserAccount::getFullname() const {
	return fullname;
}
string UserAccount::getPhonenumber() const {
	return phonenumber;
}
string UserAccount::getWalletID() const {
	return WalletID;
}
bool UserAccount::getisManager() const {
	return isManager;
}
bool UserAccount::getFirstlogin() const {
	return firstlogin;
}
void UserAccount::printInfo() const {
	cout << "Username: " << username << endl;
	cout << "Full Name: " << fullname << endl;
	cout << "Phone Number: " << phonenumber << endl;
	cout << "Wallet ID: " << WalletID << endl;
	cout << "Is Manager: " << (isManager ? "Yes" : "No") << endl;
	cout<< "First Login: " << (firstlogin ? "Yes" : "No") << endl;
}
string fakeHash(const string& input) {
	string hashed;
	for (char c : input) {
		hashed += (c + 3);
	}
	return hashed;
}
string generateRandompassword(int length) {
	string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string password;
	for (int i = 0;i < length;i++) {
		password += chars[rand() % chars.size()];
	}
	return password;
}
bool duplicateuname(const string& user) {
	ifstream inFile("users.txt");
	string line;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string uname, fullName, phone, pw, wallet;
		bool isManager, firstLogin;

		getline(ss, uname, ',');
		getline(ss, fullName, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;

		if (user == uname) {
			inFile.close();
			return true;
		}
	}

	inFile.close();
	return false;
}
UserAccount createUserfrominput() {
	string uname, name, phone, password;
	bool isManager;
	bool check = true;
	while (check == true) {
		cout << "Username:";
		getline(cin, uname);
		if (duplicateuname(uname)) {
			check = true;
			cout << "[x] Username existed\n";
			continue;
		}
		check = false;
		cout << "Fullname:";
		getline(cin, name);
		cout << "PhoneNumber:";
		getline(cin, phone);
		cout << "Is Manager ? (1 = Yes, 0 = No) :";
		cin >> isManager;
		cin.ignore();
		cout << "Input password (empty to create random password) ";
		getline(cin, password);
		if (password.empty()) {
			password = generateRandompassword(8);
			cout << "Your random password :" << password << endl;
		}
	}

	UserAccount user(uname, name, phone, isManager);
	user.setPassword(fakeHash(password));
	return user;
}
void saveUsertofile(const UserAccount& user, const string& filename) {
	ofstream file(filename, ios::app);
	file << user.getUsername() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getPasswordHash() << "," << user.getWalletID() << "," << user.getisManager() << "," << user.getFirstlogin() << endl;
	file.close();
	ofstream backup("users_backup.txt", ios::app);
	backup << user.getUsername() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getPasswordHash() << "," << user.getWalletID() << "," << user.getisManager() << "," << user.getFirstlogin() << endl;
	backup.close();
}
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename,const string& backupfilename) {
	ifstream inFile(filename);
	ofstream tempFile("temp.txt");
	ofstream tempBackupFile("temp_backup.txt");
	string line;
	bool updated = false;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string uname, fullName, phone, pw, wallet;
		bool isManager, firstLogin;

		getline(ss, uname, ',');
		getline(ss, fullName, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;

		if (uname == username) {
			pw = newPassword;
			firstLogin = false;
			updated = true;
		}

		tempFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
		tempBackupFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
	}

	inFile.close();
	tempFile.close();
	tempBackupFile.close();

	if (remove(filename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp.txt", filename.c_str()) != 0) {
		perror("Error renaming temp file");
	}
	if (remove(backupfilename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp_backup.txt", backupfilename.c_str()) != 0) {
		perror("Error renaming temp file");
	}


	return updated;
}
bool updateFullnameInFile(const string& username, const string& newFullname, const string& filename, const string& backupfilename) {
	ifstream inFile(filename);
	ofstream tempFile("temp.txt");
	ofstream tempBackupFile("temp_backup.txt");
	string line;
	bool updated = false;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string uname, fullName, phone, pw, wallet;
		bool isManager, firstLogin;

		getline(ss, uname, ',');
		getline(ss, fullName, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;

		if (uname == username) {
			fullName = newFullname;
		}

		tempFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
		tempBackupFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
	}

	inFile.close();
	tempFile.close();
	tempBackupFile.close();

	if (remove(filename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp.txt", filename.c_str()) != 0) {
		perror("Error renaming temp file");
	}
	if (remove(backupfilename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp_backup.txt", backupfilename.c_str()) != 0) {
		perror("Error renaming temp file");
	}


	return updated;
}
bool updatePhonenumberInFile(const string& username, const string& newPhonenumber, const  string& filename, const string& backupfilename) {
	ifstream inFile(filename);
	ofstream tempFile("temp.txt");
	ofstream tempBackupFile("temp_backup.txt");
	string line;
	bool updated = false;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string uname, fullName, phone, pw, wallet;
		bool isManager, firstLogin;

		getline(ss, uname, ',');
		getline(ss, fullName, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;

		if (uname == username) {
			phone = newPhonenumber;
		}

		tempFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
		tempBackupFile << uname << ',' << fullName << ',' << phone << ','
			<< pw << ',' << wallet << ',' << isManager << ',' << firstLogin << '\n';
	}

	inFile.close();
	tempFile.close();
	tempBackupFile.close();

	if (remove(filename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp.txt", filename.c_str()) != 0) {
		perror("Error renaming temp file");
	}
	if (remove(backupfilename.c_str()) != 0) {
		perror("Error deleting original file");
	}
	if (rename("temp_backup.txt", backupfilename.c_str()) != 0) {
		perror("Error renaming temp file");
	}


	return updated;
}

void showUserMenu(const string& username) {
	cout << "\n===== USER MENU =====\n";
	cout << "1. View personal information\n";
	cout << "2. Change password\n";
	cout << "3. Exit\n";
	int choice;
	cin >> choice;
	cin.ignore();
	if (choice == 1) {
		ifstream file("users.txt");
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string uname, fullname, phone, pw, wallet;
			bool isManager, firstLogin;
			getline(ss, uname, ',');
			getline(ss, fullname, ',');
			getline(ss, phone, ',');
			getline(ss, pw, ',');
			getline(ss, wallet, ',');
			ss >> isManager;
			ss.ignore();
			ss >> firstLogin;
			if (uname == username) {
				cout << "\nUsername: " << uname
					<< "\nFullname: " << fullname
					<< "\nPhone: " << phone
					<< "\nWallet ID: " << wallet
					<< "\nRole: " << (isManager ? "Admin" : "User") << endl;
				break;
			}
			
		}
		file.close();
	}
	else if (choice == 2) {
		cout << "New password: ";
		string newPass;
		getline(cin, newPass);
		updatePasswordInFile(username, fakeHash(newPass), "users.txt", "users_backup.txt");
		cout << "[✓] Password changed successfully.\n";
	}
}

bool checkusername(const string& username) {
	ifstream file("users.txt");
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string uname, fullname, phone, pw, wallet;
		bool isManager, firstLogin;
		getline(ss, uname, ',');
		getline(ss, fullname, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;
		if (uname == username) {
			return true;
		}
	}

	file.close();
	return false;
}

void showAdminMenu() {
	cout << "\n===== ADMIN MENU =====\n";
	cout << "1. View user list\n";
	cout << "2. Create new account\n";
	cout << "3. Edit user\n";
	cout << "4. Exit\n";
	int choice;
	cin >> choice;
	cin.ignore();
	if (choice == 1) {
		ifstream file("users.txt");
		string line;
		cout << "\n--- user list ---\n";
		while (getline(file, line)) {
			stringstream ss(line);
			string uname, fullname, phone, pw, wallet;
			bool isManager, firstLogin;
			getline(ss, uname, ',');
			getline(ss, fullname, ',');
			getline(ss, phone, ',');
			getline(ss, pw, ',');
			getline(ss, wallet, ',');
			ss >> isManager;
			ss.ignore();
			ss >> firstLogin;
			cout << "Username: " << uname << ", Fullname: " << fullname
				<< ", Phone: " << phone << ", Role: " << (isManager ? "Admin" : "User") << endl;
		}
		file.close();
	}
	else if (choice == 2) {
		UserAccount user = createUserfrominput();
		saveUsertofile(user, "users.txt");
		cout << "[✓] Account created successfully\n";
	}
	else if (choice == 3) {
		bool condition = true;
		while (condition) {
			cout << "Username: ";
			string username;
			cin >> username;
			if (checkusername(username)) {
				condition = false;
				bool editMore = true;
				while (editMore) {
					cout << "The information you want to change is " << username << "\n";
					cout << "1. Fullname\n2. Phonenumber\n3. Password\n";
					int num;
					cin >> num;
					cin.ignore();

					if (num == 1) {
						string newFullname;
						cout << "Enter new fullname: ";
						getline(cin, newFullname);
						updateFullnameInFile(username, newFullname, "users.txt", "users_backup.txt");
					}
					else if (num == 2) {
						string newPhonenumber;
						cout << "Enter new phone number: ";
						getline(cin, newPhonenumber);
						updatePhonenumberInFile(username, newPhonenumber, "users.txt", "users_backup.txt");
					}
					else if (num == 3) {
						string newPassword;
						cout << "Enter new password: ";
						getline(cin, newPassword);
						updatePasswordInFile(username, newPassword, "users.txt", "users_backup.txt");
					}

					
					char choice;
					cout << "Do you want to edit more? (y/n): ";
					cin >> choice;
					cin.ignore(); 

					if (choice != 'y' && choice != 'Y') {
						editMore = false;
					}
				}
			}
		}
	}
}

bool loginAndHandleFirstLogin(const string& username, const string& password) {
	ifstream inFile("users.txt");
	string line;
	string hashedPassword = fakeHash(password);

	while (getline(inFile, line)) {
		stringstream ss(line);
		string uname, fullName, phone, pw, wallet;
		bool isManager, firstLogin;

		getline(ss, uname, ',');
		getline(ss, fullName, ',');
		getline(ss, phone, ',');
		getline(ss, pw, ',');
		getline(ss, wallet, ',');
		ss >> isManager;
		ss.ignore();
		ss >> firstLogin;

		if (uname == username && pw == hashedPassword) {
			if (firstLogin) {
				cout << "[!] first login. change your password please:\n Input new password: ";
				string newPass;
				getline(cin, newPass);
				inFile.close();
				updatePasswordInFile(username, fakeHash(newPass), "users.txt", "users_backup.txt");
				ifstream inFile("users.txt");
				cout << "[✓] Complete change.\n";
			}
			else {
				cout << "[✓] Successful login.\n";
				if (isManager == 0) {
					inFile.close();
					showUserMenu(uname);
				}
				else {
					inFile.close();
					showAdminMenu();
				}
			}
			return true;
		}
	}
	inFile.close();
	return false;
}
Transation ::Transation(const string& From, const string& To, const int& Am, const bool& sta) {
	FromID = From;
	ToID = To;
	Amount = Am;
	status = sta;
}
Wallet::Wallet(const string& ID) {
	WalletID = ID;
	balance = 1000000;
}
string Wallet:: getID() const {
	return WalletID;
}
int Wallet::getBalance() const {
	return balance;
}
OTPManager otpManager;   // INTIATE otpManager belonging to OTP class (cua Phat)
void updateUserInfo(const string& username, const string& newName, const string& newPhone) { //                     -FUNCTION TO UPDATE USER'S INFO-
    ifstream inFile("users.txt");
    ofstream tempFile("temp_users.txt");
    string line;
        while (getline(inFile, line)) {
        stringstream ss(line);
        string uname, fullname, phone, pw, wallet;
        bool isManager, firstLogin;
        getline(ss, uname, ',');
        getline(ss, fullname, ',');
        getline(ss, phone, ',');
        getline(ss, pw, ',');
        getline(ss, wallet, ',');
        ss >> isManager;
        ss.ignore();
        ss >> firstLogin;

        if (uname == username) {
            fullname = newName;
            phone = newPhone;
        }

        tempFile << uname << ',' << fullname << ',' << phone << ',' << pw << ',' << wallet
                 << ',' << isManager << ',' << firstLogin << '\n';
    }

    inFile.close();
    tempFile.close();
    remove("users.txt");
    rename("temp_users.txt", "users.txt");
}

void requestInfoChange(const string& username) {         //                                                         -FUNCTION TO REQUEST CHANGE OF INFO-
    cout << "[!] Xác thực bằng OTP để thay đổi thông tin.\n";
    otpManager.sendOTP(username);
    
    cout << "Nhập OTP được gửi: ";
    string inputOtp;
    getline(cin, inputOtp);

    if (!otpManager.checkOTP(username, inputOtp)) {
        cout << "[X] OTP không đúng hoặc đã hết hạn.\n";
        return;
    }

    string newName, newPhone;
    cout << "Nhập tên mới: ";
    getline(cin, newName);
    cout << "Nhập số điện thoại mới: ";
    getline(cin, newPhone);

    ofstream reqFile("requests.txt", ios::app);
    reqFile << username << "," << newName << "," << newPhone << "\n";
    reqFile.close();
    cout << "[✓] Yêu cầu thay đổi đã được gửi đến admin.\n";
}
void showUserMenu(const string& username) { //                                                                            ~~ USER PANEL ~~
    cout << "\n-=====- USER MENU -=====-\n";
    cout << "1. Xem thông tin cá nhân\n";
    cout << "2. Đổi mật khẩu\n";
    cout << "3. Yêu cầu thay đổi thông tin\n";
    cout << "4. Thoát\n";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string uname, fullname, phone, pw, wallet;
            bool isManager, firstLogin;
            getline(ss, uname, ',');
            getline(ss, fullname, ',');
            getline(ss, phone, ',');
            getline(ss, pw, ',');
            getline(ss, wallet, ',');
            ss >> isManager;
            ss.ignore();
            ss >> firstLogin;
            if (uname == username) {
                cout << "\nUsername: " << uname
                     << "\nFullname: " << fullname
                     << "\nPhone: " << phone
                     << "\nWallet ID: " << wallet
                     << "\nRole: " << (isManager ? "Admin" : "User") << endl;
                break;
            }
        }
        file.close();
    } else if (choice == 2) {
        cout << "Nhập mật khẩu mới: ";
        string newPass;
        getline(cin, newPass);
        updatePasswordInFile(username, fakehash(newPass), "users.txt");
        cout << "[✓] Mật khẩu đã được thay đổi.\n";
    } else if (choice == 3) {
        requestInfoChange(username);
    } else if (choice == 4) {
        return;
    }
}
void showAdminMenu() {  //                                                                                              ~~ ADMIN PANEL ~~
    cout << "\n-=====- ADMIN MENU -=====-\n";
    cout << "1. Xem danh sách người dùng\n";
    cout << "2. Tạo tài khoản mới\n";
    cout << "3. Duyệt yêu cầu thay đổi thông tin.\n";
    cout << "4. Thoát\n";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        ifstream file("users.txt");
        string line;
        cout << "\n--- Danh sách người dùng ---\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string uname, fullname, phone, pw, wallet;
            bool isManager, firstLogin;
            getline(ss, uname, ',');
            getline(ss, fullname, ',');
            getline(ss, phone, ',');
            getline(ss, pw, ',');
            getline(ss, wallet, ',');
            ss >> isManager;
            ss.ignore();
            ss >> firstLogin;
            cout << "Username: " << uname << ", Fullname: " << fullname
                 << ", Phone: " << phone << ", Role: " << (isManager ? "Admin" : "User") << endl;
        }
        file.close();
    } else if (choice == 2) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user, "users.txt");
        cout << "[✓] Tạo tài khoản thành công.\n";
    } else if (choice == 3) {
    ifstream reqFile("requests.txt");
    vector<string> remainingRequests;
    string line;
    while (getline(reqFile, line)) {
        stringstream ss(line);
        string uname, newName, newPhone;
        getline(ss, uname, ',');
        getline(ss, newName, ',');
        getline(ss, newPhone, ',');
    cout << "\n[!] Yêu cầu từ: " << uname
             << "\nTên mới: " << newName
             << "\nSĐT mới: " << newPhone << endl;

        cout << "Phê duyệt thay đổi này? (y/n): ";
        char approve;
        cin >> approve;
        cin.ignore();

        if (approve == 'y' || approve == 'Y') {
            updateUserInfo(uname, newName, newPhone);
            cout << "[✓] Đã cập nhật thông tin người dùng.\n";
        } else {
            remainingRequests.push_back(line);
        }
    }
    reqFile.close();

                                // Save remaining unapproved requests 
    ofstream outFile("requests.txt");
    for (const string& req : remainingRequests)
        outFile << req << "\n";
        outFile.close();
}
}



