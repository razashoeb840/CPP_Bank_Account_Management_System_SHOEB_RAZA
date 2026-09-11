#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "1_Account.h"

class CurrentAccount:public Account{
private:
    double overdraftLimit;

public:
    CurrentAccount(int accountNumber,string name,double balance,double overdraftLimit);

    bool withdraw(double amount);
    void showDetails();
    string getAccountType();
};

#endif
