#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

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
UserAccount createUserfrominput() {
	string uname, name, phone, password;
	bool isManager;
	cout << "Username:";
	getline(cin, uname);
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
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename) {
	ifstream inFile("users.txt");
	ofstream tempFile("temp.txt");
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
	}

	inFile.close();
    tempFile.close();

    if (remove(filename.c_str()) != 0) {
        perror("Error deleting original file");
    }
    if (rename("temp.txt", filename.c_str()) != 0) {
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

		inFile.close();

		if (uname == username && pw == hashedPassword) {
			if (firstLogin) {
				cout << "[!] first login. change your password please:\n Input new password: ";
				string newPass;
				getline(cin, newPass);
				updatePasswordInFile(username, fakehash(newPass), "users.txt");
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

int main() {
    srand(time(0));
    int choice;
    cout << "1. Register\n2. Sign Up\n Make choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user,"users.txt");
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
