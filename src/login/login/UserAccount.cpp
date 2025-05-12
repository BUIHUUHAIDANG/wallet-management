#include "UserAccount.h"
#include<iostream>
#include <cstdlib>



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
		return hashed;
	}
}
string generateRamdompassword(int length) {
	string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string password;
	for (int i = 0;i < length;i++) {
		password += chars[rand() % chars.size()];
	}
	return password;
}
UserAccount createUserfrominput() {
	string uname, name, phone, password;
	bool isManager;
	cout << "Ten tai khoan cua ban la:";
	getline(cin, uname);
	cout << "Ten day du cua ban la:";
	getline(cin, name);
	cout << "So dien thoai cua ban la:";
	getline(cin, phone);
	cout << "Tai khoan nay la cua quan ly (1 = Co, 0 = Khong)";
	cin >> isManager;
	cin.ignore();
	cout << "Nhap mat khau (bo trong de tu dong tao): ";
	getline(cin, password);
	if (password.empty()) {
		password = generateRamdompassword(8);
		cout << "mat khau tu dong cua ban la:" << password << endl;
	}
	UserAccount user(uname, name, phone, isManager);
	user.setPassword(fakehash(password));
	return user;
}

