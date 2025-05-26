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
// l?y input password t? user sau ?� b?m ra ?? l?u v�o file c?ng nh? b?m password khi ??ng nh?p. 
string fakeHash(const string& input);
// h�m t? ??ng t?o m?t kh?u khi user b? tr?ng � m?t kh?u.
string generateRandompassword(int length);
// h�m ki?m tra xem t�n ??ng nh?p ?� t?n t?i hay ch?a.
bool duplicateuname(const string& user);
// h�m t?o t�i kho?n ng??i d�ng t? input c?a ng??i d�ng.
UserAccount createUserfrominput();
// h�m l?u th�ng tin ng??i d�ng v�o file l?y d? li?u truy?n v�o t? h�m constructor c?a UserAccount.
void saveUsertofile(const UserAccount& user, const string& filename);
// h�m c?p nh?t m?t kh?u trong file g?c v� file backup khi thay ??i m?t kh?u.
bool updatePasswordInFile(const string& username, const string& newPassword, const string& filename, const string& backupfilename);
// h�m c?p nh?t t�n ??y ?? trong file g?c v� file backup khi thay ??i t�n ??y ??.
bool updateFullnameInFile(const string& username, const string& newFullname, const string& filename, const string& backupfilename);
// h�m c?p nh?t s? ?i?n tho?i trong file g?c v� file backup khi thay ??i s? ?i?n tho?i.
bool updatePhonenumberInFile(const string& username, const string& newPhonenumber, const string& filename, const string& backupfilename);
// n?i l?u tr? OTP v?i username l� key, pair<string, time_t> l� gi� tr? g?m OTP v� th?i gian t?o OTP.
extern map<string, pair<string, time_t>> otpStore;
// h�m t?o OTP ng?u nhi�n v?i k�ch th??c m?c ??nh l� 6 k� t?.
string generateOTP(int size);
// h�m tr? v? gi� tr? TTL (Time To Live) cho OTP, m?c ??nh l� 180 gi�y.
int getTTL();
// h�m g?i OTP cho ng??i d�ng, l?u v�o otpStore v?i th?i gian t?o OTP.
void sendOTP(const string& username, int ttl);
// h�m ki?m tra OTP, so s�nh v?i gi� tr? trong otpStore v� ki?m tra th?i gian h?t h?n.
bool checkOTP(const string& username, const string& input, int ttl);
// h�m y�u c?u ng??i d�ng thay ??i th�ng tin c� nh�n, g?i OTP ?? x�c th?c.
void requestInfoChange(const string& username);
// h�m hi?n th? menu ng??i d�ng, cho ph�p xem th�ng tin c� nh�n, ??i m?t kh?u, y�u c?u thay ??i th�ng tin v� qu?n l� v�.
void showUserMenu(const string& username);
// h�m ki?m tra xem t�n ??ng nh?p c� h?p l? hay kh�ng, t?c l� kh�ng ch?a k� t? ??c bi?t v� kh�ng r?ng.
bool checkusername(const string& username);
// h�m hi?n th? menu qu?n tr? vi�n, cho ph�p qu?n l� ng??i d�ng v� x? l� y�u c?u thay ??i th�ng tin.
void showAdminMenu();
// h�m ??ng nh?p v� x? l� ??ng nh?p l?n ??u, tr? v? true n?u ??ng nh?p th�nh c�ng v� false n?u kh�ng th�nh c�ng.
bool loginAndHandleFirstLogin(const string& username, const string& password);




#endif
