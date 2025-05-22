
#ifndef WALLET_H
#define WALLET_H
#include<string>
using namespace std;
class Wallet {
private:
    string wallet_id;       
    string transaction;     // Ví dụ: A to B
    string remainder;          // Số dư còn lại
public:
    // Constructor
    Wallet(const string& wid, const string& rmd, const string& tst);
    string getwalletid() const;
    string getremainder() const;
    string gettransaction() const;
    void display() const;
};
bool receipt(const string& depositor, const string& rcp, const int& amt);
void transfer(const string& depositor, const string& rcp, const int& amt);
Wallet createwallet(const string& uname);
void savewallettofile(const Wallet& mywallet, const string& filename);
#endif
