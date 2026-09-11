#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "1_Account.h"

class SavingsAccount:public Account{
private:
    double interestRate;

public:
    SavingsAccount(int accountNumber,string name,double balance,double interestRate);

    void addInterest();
    void showDetails();
    string getAccountType();
};

#endif
