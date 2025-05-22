#include "Wallett.h"
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
Wallet::Wallet(const string& wid /*wallet_id*/, const string& rmd /*remainder*/, const string& tst /*transaction*/) {
	wallet_id = wid;
	remainder = rmd;
	transaction = tst;
}

string Wallet::getwalletid() const {
	return wallet_id;
}
string Wallet::getremainder() const {
	return remainder;
}
string Wallet::gettransaction() const {
	return transaction;
}
void Wallet::display() const {
	cout << "\n=== WALLET ===" << endl;
	cout << "Wallet ID       : " << wallet_id << endl;
	cout << "Remainder       : " << remainder << endl;
	cout << "Transaction	: " << (transaction.empty() ? "Empty" : transaction) << endl;
}

bool receipt(const string& depositor, const string& rcp, const int& amt) {
	ifstream file("wallet_id_" + rcp + ".txt");
	string wid, transaction, remainder;
	getline(file, wid, ',');
	getline(file, remainder, ',');
	getline(file, transaction);

	file.close();

	int remain = stoi(remainder);

	remain += amt;

	remainder = to_string(remain);

	transaction += "Receipt " + to_string(amt) + " from " + depositor + ",";

	ofstream tempfile("temp.txt");
	tempfile << rcp << "," << remainder << "," << transaction;
	tempfile.close();

	if (remove(("wallet_id_" + rcp + ".txt").c_str()) != 0) {
		perror("Error deleting original file");
		cout << "Transaction not processed";
		return false;
	}
	if (rename("temp.txt", (("wallet_id_" + rcp + ".txt").c_str())) != 0) {
		perror("Error renaming temp file");
		cout << "Transaction not processed";
		return false;
	}

	return true;
}

void transfer(const string& depositor, const string& rcp, const int& amt) {
	ifstream file("wallet_id_" + depositor + ".txt");
	string wid, transaction, remainder;
	getline(file, wid, ',');
	getline(file, remainder, ',');
	getline(file, transaction);

	file.close();

	if (amt <= 0) {
		cout << "[!] Invalid amount" << endl;
		return;
	}

	int remain = stoi(remainder);

	// Atomicity + Consistency
	if (amt > remain) {
		cout << "[!] Your transaction was declined due to insufficient funds." << endl;
		return;
	}
	else {

		if (!receipt(depositor, rcp, amt)) {
			cout << "Transaction not processed";
			return;
		}

		remain -= amt;
		remainder = to_string(remain);
		transaction += "Transfer to " + rcp + " amount " + to_string(amt) + ",";


		// Durability
		ofstream tempfile("temp.txt");
		tempfile << depositor << "," << remainder << "," << transaction;
		tempfile.close();
		if (remove(("wallet_id_" + depositor + ".txt").c_str()) != 0) {
			perror("Error deleting original file");
			cout << "Transaction not processed";
			return;
		}
		if (rename("temp.txt", (("wallet_id_" + depositor + ".txt").c_str())) != 0) {
			perror("Error renaming temp file");
			cout << "Transaction not processed";
			return;
		}

		cout << "Transferred " + to_string(amt) + " to " + rcp;
	}
}
Wallet createwallet(const string& uname) {
	string wid, tst;
	string rmd = "1000000";
	wid = uname;
	Wallet mywallet(wid, rmd, tst);
	return mywallet;
}
void savewallettofile(const Wallet& mywallet, const string& filename) {
	ofstream file(filename, ios::app);
	file << mywallet.getwalletid() << "," << mywallet.getremainder() << mywallet.gettransaction();
	file.close();
}