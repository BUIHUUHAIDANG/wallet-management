#ifndef OTP_H
#define OTP_H 
// Ngăn tái định nghĩa nếu otp.h được include nhiều lần

#include <string>
#include <map>
#include <ctime>

using namespace std;

// Khai báo biến toàn cục
extern map<string, pair<string, time_t>> otpStore;
//extern đảm bảo dùng một lần trong otp.cpp và định nghĩa cho file otp.cpp( lưu ý phần externextern)
// Khai báo hàm
string generateOTP(int size);
int getTTL();
void sendOTP(const string& username, int ttl);
bool checkOTP(const string& username, const string& input, int ttl);

#endif