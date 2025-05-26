#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include<vector>
#include <string>
#include<map>
#include <ctime>

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
	//constuctor co tham so ban dau->de khoi tao user  .
	UserAccount(const string& uname, const string& name, const string& phone, bool manager = false);
	//dat mat khau.
	void setPassword(const string& pw);
	//de biet user da dang nhap lan dau hay chua.
	void setFirstLogin(bool status);
	//lay mat khau da ma hoa.
	string getPasswordHash() const;
	//lay ten dang nhap
	string getUsername() const;
	//lay ten day du.
	string getFullname() const;
	//lay so dien thoai.
	string getPhonenumber() const;
	//lay id vi.
	string getWalletID() const;
	//kiem tra xem user co phai la quan tri vien hay khong.
	bool getisManager() const;
	//kiem tra xem user da dang nhap lan dau hay chua.
	bool getFirstlogin() const;
	//in thong tin user.
	void printInfo() const;

};
// l?y input password t? user sau ?ó b?m ra ?? l?u vào file c?ng nh? b?m password khi ??ng nh?p. 
string fakeHash(const string& input);
// hàm t? ??ng t?o m?t kh?u khi user b? tr?ng ô m?t kh?u.
string generateRandompassword(int length);
// hàm ki?m tra xem tên ??ng nh?p ?ã t?n t?i hay ch?a.
bool duplicateuname(const string& user);
// hàm t?o tài kho?n ng??i dùng t? input c?a ng??i dùng.
UserAccount createUserfrominput();
// hàm l?u thông tin ng??i dùng vào file l?y d? li?u truy?n vào t? hàm constructor c?a UserAccount.
void saveUsertofile(const UserAccount& user, const string& filename);
// hàm c?p nh?t m?t kh?u trong file g?c và file backup khi thay ??i m?t kh?u.
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename, const string& backupfilename);
// hàm c?p nh?t tên ??y ?? trong file g?c và file backup khi thay ??i tên ??y ??.
bool updateFullnameInFile(const string& username, const string& newFullname, const string& filename, const string& backupfilename);
// hàm c?p nh?t s? ?i?n tho?i trong file g?c và file backup khi thay ??i s? ?i?n tho?i.
bool updatePhonenumberInFile(const string& username, const string& newPhonenumber, const string& filename, const string& backupfilename);
// n?i l?u tr? OTP v?i username là key, pair<string, time_t> là giá tr? g?m OTP và th?i gian t?o OTP.
extern map<string, pair<string, time_t>> otpStore;
// hàm t?o OTP ng?u nhiên v?i kích th??c m?c ??nh là 6 ký t?.
string generateOTP(int size);
// hàm tr? v? giá tr? TTL (Time To Live) cho OTP, m?c ??nh là 180 giây.
int getTTL();
// hàm g?i OTP cho ng??i dùng, l?u vào otpStore v?i th?i gian t?o OTP.
void sendOTP(const string& username, int ttl);
// hàm ki?m tra OTP, so sánh v?i giá tr? trong otpStore và ki?m tra th?i gian h?t h?n.
bool checkOTP(const string& username, const string& input, int ttl);
// hàm yêu c?u ng??i dùng thay ??i thông tin cá nhân, g?i OTP ?? xác th?c.
void requestInfoChange(const string& username);
// hàm hi?n th? menu ng??i dùng, cho phép xem thông tin cá nhân, ??i m?t kh?u, yêu c?u thay ??i thông tin và qu?n lý ví.
void showUserMenu(const string& username);
// hàm ki?m tra xem tên ??ng nh?p có h?p l? hay không, t?c là không ch?a ký t? ??c bi?t và không r?ng.
bool checkusername(const string& username);
// hàm hi?n th? menu qu?n tr? viên, cho phép qu?n lý ng??i dùng và x? lý yêu c?u thay ??i thông tin.
void showAdminMenu();
// hàm ??ng nh?p và x? lý ??ng nh?p l?n ??u, tr? v? true n?u ??ng nh?p thành công và false n?u không thành công.
bool loginAndHandleFirstLogin(const string& username, const string& password);




#endif
