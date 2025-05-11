#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include <string>
using namespace std;
class UserAccount {
private:
    string username;
    string fullName;
    string phoneNumber;
    string passwordHash;
    string walletId;
    bool isManager;
    bool firstLogin;

public:
    UserAccount(const string& uname, const string& name, const string& phone, bool manager = false);

    void setPassword(const string& hash);
    void setFirstLogin(bool status);

    string getUsername() const;
    string getFullName() const;
    string getPhoneNumber() const;
    string getPasswordHash() const;
    string getWalletId() const;
    bool getIsManager() const;
    bool getFirstLogin() const;
    void printInfo() const;
};

std::string fakeHash(const std::string& input);
std::string generateRandomPassword(int length = 8);
UserAccount createUserFromInput();
void saveUserToFile(const UserAccount& user, const std::string& filename = "users.txt");
bool updatePasswordInFile(const std::string& username, const std::string& newPassword, const std::string& filename = "users.txt");
bool loginAndHandleFirstLogin(const std::string& username, const std::string& password);

#endif
