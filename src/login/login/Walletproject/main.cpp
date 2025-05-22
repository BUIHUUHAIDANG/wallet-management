#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#define OTP_H
using namespace std;

extern map<string, pair<string, time_t>> otpStore;
string generateOTP(int size);
int getTTL();
void sendOTP(const string& username, int ttl);
bool checkOTP(const string& username, const string& input, int ttl);
map<string, pair<string, time_t>> otpStore;


string generateOTP(int size = 6) {
    static bool seeded = false;
        if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    const string digits = "0123456789";
    string result;
    result.reserve(size);

    for (int i = 0; i < size; ++i)
        result += digits[rand() % digits.size()];

    return result;
}


int getTTL() {
    return 180;
}

void sendOTP(const string& username, int ttl = 180) {
    string otp = generateOTP();
    otpStore[username] = {otp, time(nullptr)};//***
    cout << "Your OTP is: " << otp << " (Time limit: " << ttl << " seconds)" << endl;
}

bool checkOTP(const string& username, const string& input, int ttl = 180) {
    auto it = otpStore.find(username);
    if (it == otpStore.end()) return false;

    const auto& entry = it->second;
    double timeElapsed = difftime(time(nullptr), entry.second);
    bool isExpired = timeElapsed > ttl;
    bool isValid = !isExpired && entry.first == input;
    cout << "Time elapsed: " << timeElapsed << " seconds, Expired: " << (isExpired ? "Yes" : "No") << endl;
    return isValid;
}
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
	cout << "First Login: " << (firstlogin ? "Yes" : "No") << endl;
}

class Wallet {
private:
    string wallet_id;       // ID của ví
    string transaction;     // Ví dụ: A to B
    int amount;             // Số lượng chuyển
    string remainder;          // Số dư còn lại
public:
    // Constructor
    Wallet(const string& wid, const string& rmd, const string& tst);
	string getwalletid() const;
	string getremainder() const;
	string gettransaction() const;
	void display() const;
};

Wallet::Wallet(const string& wid /*wallet_id*/, const string& rmd /*remainder*/, const string& tst /*transaction*/) {
	wallet_id = wid;
	remainder = rmd;
	transaction = tst;
}

string Wallet::getwalletid () const {
	return wallet_id;
}
string Wallet::getremainder () const {
	return remainder;
}
string Wallet::gettransaction () const {
	return transaction;
}
void Wallet::display () const {
	cout << "\n=== WALLET ===" << endl;
    cout << "Wallet ID       : " << wallet_id << endl;
	cout << "Remainder       : " << remainder << endl;
    cout << "Transaction	: " << (transaction.empty() ? "Empty" : transaction) << endl;
}

bool receipt(const string& depositor, const string& rcp, const int& amt) {
	ifstream file("wallet_id_" + rcp + ".txt");
	string wid, transaction, remainder;
	getline(file, wid, ',');
	getline(file, remainder, ',');
	getline(file, transaction);

	file.close();

	int remain = stoi(remainder);

	remain += amt;

	remainder = to_string(remain);

	transaction += "Receipt " + to_string(amt) + " from " + depositor + ",";

	ofstream tempfile ("temp.txt");
	tempfile << rcp << "," << remainder << "," << transaction;
	tempfile.close();

	if (remove(("wallet_id_" + rcp + ".txt").c_str()) != 0) {
		perror("Error deleting original file");
		cout << "Transaction not processed";
		return false;
	}
	if (rename("temp.txt", (("wallet_id_" + rcp + ".txt").c_str())) != 0) {
		perror("Error renaming temp file");
		cout << "Transaction not processed";
		return false;
	}

	return true;
}

void transfer(const string& depositor, const string& rcp, const int& amt) {
	ifstream file("wallet_id_" + depositor + ".txt");
	string wid, transaction, remainder;
	getline(file, wid, ',');
	getline(file, remainder, ',');
	getline(file, transaction);

	file.close();

	if (amt <= 0) {
		cout << "[!] Invalid amount" << endl;
		return;
	}

	int remain = stoi(remainder);

	// Atomicity + Consistency
	if (amt > remain) {
//		cout << amt << ", " << remain << ", " << remainder;
		cout << "[!] Your transaction was declined due to insufficient funds." << endl;
		return;
	} else {

		if(!receipt(depositor, rcp, amt)) {
			cout << "Transaction not processed";
			return;
		}

		remain -= amt;
		remainder = to_string(remain);
		transaction += "Transfer to " + rcp + " amount " + to_string(amt) + ",";


		// Durability
		ofstream tempfile("temp.txt");
		tempfile << depositor << "," << remainder << "," << transaction;
		tempfile.close();
		if (remove(("wallet_id_" + depositor + ".txt").c_str()) != 0) {
			perror("Error deleting original file");
			cout << "Transaction not processed";
			return;
		}
		if (rename("temp.txt", (("wallet_id_" + depositor + ".txt").c_str())) != 0) {
			perror("Error renaming temp file");
			cout << "Transaction not processed";
			return;
		}

		cout << "Transferred " + to_string(amt) + " to " + rcp;
	}
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

Wallet createwallet(const string& uname) {
	string wid, tst;
	string rmd = "1000000";

	wid = uname;

	Wallet mywallet(wid, rmd, tst);
	return mywallet;
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
            cout << "[x] Username existed.\n";
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

void savewallettofile(const Wallet& mywallet, const string& filename) {
	ofstream file(filename, ios::app);
	file << mywallet.getwalletid() << "," << mywallet.getremainder() << mywallet.gettransaction();
	file.close();
}

void saveUsertofile(const UserAccount& user, const string& filename) {
	ofstream file(filename, ios::app);
	file << user.getUsername() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getPasswordHash() << "," << user.getWalletID() << "," << user.getisManager() << "," << user.getFirstlogin() << endl;
	file.close();
	ofstream backup("users_backup.txt", ios::app);
	backup << user.getUsername() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getPasswordHash() << "," << user.getWalletID() << "," << user.getisManager() << "," << user.getFirstlogin() << endl;
	backup.close();
}
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename, const string& backupfilename) {
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

bool checkusername (const string& username) {
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

void requestInfoChange(const string& username) {         //                                                         -FUNCTION TO REQUEST CHANGE OF INFO-
    cout << "[!] Verify with OTP.\n";
    sendOTP(username);

    cout << "OTP sent. ";
    string inputOtp;
    getline(cin, inputOtp);

    if (!checkOTP(username, inputOtp)) {
        cout << "[X] Invalid OTP.\n";
        return;
    }

    string newName, newPhone;
    cout << "New name:";
    getline(cin, newName);
    cout << "New phone number: ";
    getline(cin, newPhone);

    ofstream reqFile("requests.txt", ios::app);
    reqFile << username << "," << newName << "," << newPhone << "\n";
    reqFile.close();
    cout << "[✓] Request has been sent to admin.\n";
}
void showUserMenu(const string& username) { //                                                                            ~~ USER PANEL ~~
    cout << "\n-=====- USER MENU -=====-\n";
    cout << "1. View personal information\n";
    cout << "2. Change password\n";
    cout << "3. Request to change inforamtion\n";
	cout << "4. Wallet\n";
    cout << "5. Exit\n";
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
                cout << "\nUsername: " << uname;
                cout << "\nFullname: " << fullname;
                cout << "\nPhone: " << phone;
                cout << "\nWallet ID: " << wallet;
                cout << "\nRole: " << (isManager ? "Admin" : "User") << endl;
                break;
            }
        }
        file.close();
    } else if (choice == 2) {
        cout << "Enter the new passowrd: ";
        string newPass;
        getline(cin, newPass);
        updatePasswordInFile(username, fakehash(newPass), "users.txt","users_backup.txt");
        cout << "[✓] Password changed.\n";
    } else if (choice == 3) {
        requestInfoChange(username);
    } else if (choice == 4) {
		ifstream file("wallet_id_" + username + ".txt");
		string wid, transaction, temptrans, remainder;
		getline(file, wid, ',');
		getline(file, remainder, ',');
		while(getline(file, transaction, ',')) {
			temptrans += "\n" + transaction;
		}

		file.close();

		Wallet mywallet (wid, remainder, temptrans);

		cout << "\n===== MENU =====" << endl;
		cout << "1. Show wallet information" << endl;
		cout << "2. Transfer" << endl;

		int num;
		cin >> num;

		if (num == 1) {
			mywallet.display();
		} else if (num == 2) {
			bool check = false;
			string rcp;	//Người nhận
			while (!check) {
				cout << "Transfer to [username]: ";
				string temprcp;
				cin >> temprcp;
				if (checkusername(temprcp)) {
					check = true;
					rcp = temprcp;
				} else {
					cout << "Unexist user\n";
				}
			}


			cout << "Amount: ";
			int amt;				//Số lượng chuyển
			cin >> amt;
			transfer(username, rcp, amt);
		}

	} else if (choice == 5) {
        return;
    }
}
void showAdminMenu() {
    int choice;
        cout << "\n-=====- ADMIN MENU -=====-\n";
        cout << "1. View user list\n";
        cout << "2. Create new account\n";
        cout << "3. Approve information change requests\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            ifstream file("users.txt");
            if (!file) {
                cout << "[x] Failed to open users.txt\n";
            } else {
                string line;
                cout << "\n--- User List ---\n";
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
                    cout << "Username: " << uname
                    << ", Fullname: " << fullname
                    << ", Phone: " << phone
                    << ", Role: " << (isManager ? "Admin" : "User") << endl;
                }
                file.close();
            }

        } else if (choice == 2) {
            UserAccount user = createUserfrominput();
            saveUsertofile(user, "users.txt");
            cout << "[✓] Account created successfully.\n";

        } else if (choice == 3) {
            ifstream reqFile("requests.txt");
            if (!reqFile) {
                cout << "[x] Failed to open requests.txt\n";
            } else {
                vector<string> remainingRequests;
                string line;

                while (getline(reqFile, line)) {
                    stringstream ss(line);
                    string uname, newName, newPhone;
                    getline(ss, uname, ',');
                    getline(ss, newName, ',');
                    getline(ss, newPhone, ',');

                    cout << "\n[!] Request from: " << uname;
                    cout << "\nNew Name: " << newName;
                    cout << "\nNew Phone number: " << newPhone << endl;

                    cout << "Approve this change? (y/n): ";
                    char approve;
                    cin >> approve;
                    cin.ignore();

                    if (approve == 'y' || approve == 'Y') {
                        updateFullnameInFile(uname,newName,"users.txt","users_backup.txt");
						updatePhonenumberInFile(uname,newPhone,"users.txt","users_backup.txt");
                        cout << "[✓] User information updated successfully.\n";
                    } else {
                        remainingRequests.push_back(line);
                    }
                }
                reqFile.close();

                ofstream outFile("requests.txt");
                for (const string& req : remainingRequests)
                    outFile << req << "\n";
                outFile.close();
            }
		} else if (choice == 4) {
            return;
       }
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
				updatePasswordInFile(username, fakehash(newPass), "users.txt", "users_backup.txt");
				ifstream inFile("users.txt");
				if (isManager == 0) {
					Wallet mywallet = createwallet(uname);
					savewallettofile(mywallet, "wallet_id_" + uname + ".txt");
				}
				cout << "[✓] Complete change.\n";
			}
			else {
				cout << "[✓] Successful login.\n";
				if (isManager == 0) {
				    inFile.close();
                    showUserMenu(username);
				} else {
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

int main() {
    srand(time(0));
    int choice;
    cout << "1. Register\n2. Sign up\nMake choice: ";
    cin >> choice;
    cin.ignore();
// function handle first login here

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
