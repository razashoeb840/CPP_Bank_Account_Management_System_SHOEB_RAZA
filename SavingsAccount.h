#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(int accountNumber, const std::string& name, double balance, double interestRate);

    void addInterest();
    void showDetails() const override;
    std::string getAccountType() const override;
};

#endif
