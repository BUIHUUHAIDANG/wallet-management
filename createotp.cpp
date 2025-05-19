#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
using namespace std;

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
};
int main(){
    // thì phải liên kết main của ông nên chưa điền vào và nhớ mấy gán username và input
}