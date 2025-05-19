#include "bestotp.h"
#include <cstdlib>// srand and rand 
using namespace std;

// Biến toàn cục để lưu trữ OTP
map<string, pair<string, time_t>> otpStore;

// Hàm tạo OTP
string generateOTP(int size = 6) {
    static bool seeded = false;// Chỉ tạo duy nhất một lần khi function bắt đấuf (tránh bị trùng otp)
        if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    const string digits = "0123456789";
    string result;
    result.reserve(size);// lưu vào file map

    for (int i = 0; i < size; ++i)
        result += digits[rand() % digits.size()];

    return result;
}

// Hàm trả về giá trị TTL
int getTTL() {
    return 180; // Giá trị TTL là 180 giây( thấy dư có thể delete )
}

// Hàm gửi OTP
void sendOTP(const string& username, int ttl = 180) {
    string otp = generateOTP();
    otpStore[username] = {otp, time(nullptr)};//*** 
    cout << "Your OTP is: " << otp << " (Time limit: " << ttl << " seconds)" << endl;
}

// Hàm kiểm tra OTP
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

int main() {
    string user = "user1";

    cout << "TTL: " << getTTL() << " seconds" << endl;
    sendOTP(user);

    string input;
    cout << "Enter OTP: ";
    cin >> input;

    if (checkOTP(user, input)) {
        cout << "OTP is correct.\n";
    } else {
        cout << "OTP is incorrect or expired.\n";
    }

    return 0;
}