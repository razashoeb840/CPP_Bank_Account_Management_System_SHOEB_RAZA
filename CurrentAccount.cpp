#include "CurrentAccount.h"

#include <iomanip>
#include <iostream>
#include <sstream>

CurrentAccount::CurrentAccount(int accountNumber, const std::string& name, double balance, double overdraftLimit)
    : Account(accountNumber, name, balance), overdraftLimit(overdraftLimit) {
}

bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid withdrawal amount.\n";
        return false;
    }

    if (amount > balance + overdraftLimit) {
        std::cout << "Withdrawal exceeds overdraft limit.\n";
        return false;
    }

    balance -= amount;

    std::ostringstream message;
    message << "Withdrawn " << std::fixed << std::setprecision(2) << amount;
    addTransaction(message.str());

    std::cout << "Amount withdrawn successfully.\n";
    return true;
}

void CurrentAccount::showDetails() const {
    Account::showDetails();
    std::cout << "Overdraft Limit: " << std::fixed << std::setprecision(2) << overdraftLimit << "\n";
}

std::string CurrentAccount::getAccountType() const {
    return "Current";
}
