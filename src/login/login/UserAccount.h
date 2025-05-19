#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include<vector>
#include <string>
using namespace std;
class UserAccount {
private:
	string username;
	string fullname;
	string passwordHash;
	string phonenumber;
	string WalletID;
	bool isManager;
	bool firstlogin;
public:
	//constuctor co tham so ban dau->de khoi tao user.
	UserAccount(const string& uname, const string& name, const string& phone, bool manager = false);
	//dat mat khau.
	void setPassword(const string& pw);
	void setFirstlogin(bool status);
	string getPasswordHash() const;
	string getUsername() const;
	string getFullname() const;
	string getPhonenumber() const;
	string getWalletID() const;
	bool getisManager() const;
	bool getFirstlogin() const;
	void printInfo() const;
	
};
string fakehash(const string& input);
string generateRandompassword(int length);
bool duplicateuname(const string& user);
UserAccount createUserfrominput();
void saveUsertofile(const UserAccount& user, const string& filename);
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename, const string& backupfilename);
bool updateFullnameInFile(const string& username, const string& newFullname, const string& filename, const string& backupfilename);
bool updatePhonenumberInFile(const string& username, const string& newPhonenumber, const string& filename, const string& backupfilename);
void showUserMenu(const string& username);
bool checkusername(const string& username);
void showAdminMenu();
bool loginAndHandleFirstLogin(const string& username, const string& password );
struct Transation
{
	string FromID;
	string ToID;
	int Amount;
	bool status;
	Transation(const string& From, const string& To, const int& Am, const bool& sta);
};
class Wallet {
private:
	string WalletID;
	int balance;
	vector<Transation>history;
public:
	Wallet(const string& ID);
	string getID() const;
	int getBalance() const;
};
#endif