#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

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
	string getUsername() const;
	string getFullname() const;
	string getPhonenumber() const;
	string getWalletID() const;
	bool getisManager() const;
	bool getFirstlogin() const;
	void printInfo() const;
	
};
string fakehash(const string& input);
string generateRamdompassword(int length);
UserAccount createUserfrominput();
#endif