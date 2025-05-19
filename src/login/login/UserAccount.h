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
	void setFirstLogin(bool status);
	string getPasswordHash() const;
	string getUsername() const;
	string getFullname() const;
	string getPhonenumber() const;
	string getWalletID() const;
	bool getisManager() const;
	bool getFirstlogin() const;
	void printInfo() const;
	
};
string fakeHash(const string& input);
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
class OTPManager {
    private:
        class OTPEntry {
            string otp;
            time_t createdAt;

        public:
            OTPEntry(string code) : otp(move(code)), createdAt(time(nullptr)) {}

            bool isExpired(int ttl = 180) const {
                return difftime(time(nullptr), createdAt) > ttl;
            }

            const string& getOTP() const {
                return otp;
            }
        };

        map<string, OTPEntry> otpStore;

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

    public:
        void sendOTP(const string& username) {
            string otp = generateOTP();
            otpStore[username] = OTPEntry(otp);
            cout << "Your OTP is: " << otp << endl;
        }

        bool checkOTP(const string& username, const string& input) {
            auto it = otpStore.find(username);
            if (it == otpStore.end()) return false;

            const OTPEntry& entry = it->second;
            return !entry.isExpired() && entry.getOTP() == input;
        }
#endif
