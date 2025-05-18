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
void UserAccount::setFirstlogin(bool status) {
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
string fakehash(const string& input) {
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
	user.setPassword(fakehash(password));
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
bool loginAndHandleFirstLogin(const string& username, const string& password) {
	ifstream inFile("users.txt");
	string line;
	string hashedPassword = fakehash(password);

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
				updatePasswordInFile(username, fakehash(newPass), "users.txt","users_backup.txt");
				ifstream inFile("users.txt");
				cout << "[✓] Complete change.\n";
			}
			else {
				cout << "[✓] successful login.\n";
			}
			return true;
		}
	}
	inFile.close();
	return false;
}



