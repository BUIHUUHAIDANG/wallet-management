#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// testing OTPManager seeing if integrating well with the functions
/* class OTPManager {
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
}; */
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
OTPManager otpManager;          // INTIATE otpManager belonging to OTP class (cua Phat)
int main() {                    // Minor changes to main()
    srand(time(0));
    int choice;
    cout << "1. Register\n2. Sign In\nMake choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        UserAccount user = createUserfrominput();
        saveUsertofile(user, "users.txt");
        cout << "[✓] Tạo tài khoản thành công.\n";
        user.printInfo();
    } else if (choice == 2) {
        string uname, password;
        cout << "Input username: ";
        getline(cin, uname);
        cout << "Input password: ";
        getline(cin, password);
        if (!loginAndHandleFirstLogin(uname, password)) {
            cout << "[X] Sai thông tin đăng nhập.\n";
        } else {
            ifstream inFile("users.txt");
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string _uname, fullname, phone, pw, wallet;
                bool isManager, firstLogin;
                getline(ss, _uname, ',');
                getline(ss, fullname, ',');
                getline(ss, phone, ',');
                getline(ss, pw, ',');
                getline(ss, wallet, ',');
                ss >> isManager;
                ss.ignore();
                ss >> firstLogin;
                if (_uname == uname) {
                    if (isManager)
                        showAdminMenu();
                    else
                        showUserMenu(uname);
                    break;
                }
            }
            inFile.close();
        }
    } else {
        cout << "[X] Invalid selection.\n";
    }
    return 0;
}