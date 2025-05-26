
#ifndef WALLET_H
#define WALLET_H
#include<string>
using namespace std;
class Wallet {
private:
	string wallet_id;       // Ví dụ: WalletID_user1
    string transaction;     // Ví dụ: A to B
    string remainder;          // Số dư còn lại
public:
    // Constructor
    Wallet(const string& wid, const string& rmd, const string& tst);
    // lấy ID ví
    string getwalletid() const;
	// lấy số dư còn lại
    string getremainder() const;
	// lấy lịch sử giao dịch
    string gettransaction() const;
	// Hiển thị thông tin ví
    void display() const;
};
// Hàm nhận tiền từ người gửi(depositor) đến người nhận(rcp) với số tiền(amt).
bool receipt(const string& depositor, const string& rcp, const int& amt);
// Hàm chuyển tiền từ người gửi(depositor) đến người nhận(rcp) với số tiền(amt).
void transfer(const string& depositor, const string& rcp, const int& amt);
// Hàm tạo ví cho người dùng với tên đăng nhập(uname).
Wallet createwallet(const string& uname);
// Hàm lưu thông tin ví vào file với tên file là filename.
void savewallettofile(const Wallet& mywallet, const string& filename);
#endif
