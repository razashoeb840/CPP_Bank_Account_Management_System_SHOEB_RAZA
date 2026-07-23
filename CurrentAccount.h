#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accountNumber, const std::string& name, double balance, double overdraftLimit);

    bool withdraw(double amount) override;
    void showDetails() const override;
    std::string getAccountType() const override;
};

#endif
