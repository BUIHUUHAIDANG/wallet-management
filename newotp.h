#ifndef otp-h//*
#define otp-h//**
#include <string> 
using namespace std;
void sendotp(const string& username);// lien quan den ham chinh name user nen check lai nha va input duoi luon
bool checkotp(const string& username,const string& input);
#endif//*