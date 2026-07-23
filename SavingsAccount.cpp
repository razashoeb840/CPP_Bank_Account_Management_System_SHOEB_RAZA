#include "SavingsAccount.h"

#include <iomanip>
#include <iostream>
#include <sstream>

SavingsAccount::SavingsAccount(int accountNumber, const std::string& name, double balance, double interestRate)
    : Account(accountNumber, name, balance), interestRate(interestRate) {
}

void SavingsAccount::addInterest() {
    double interest = balance * interestRate / 100.0;
    balance += interest;

    std::ostringstream message;
    message << "Interest added " << std::fixed << std::setprecision(2) << interest;
    addTransaction(message.str());

    std::cout << "Interest added successfully.\n";
}

void SavingsAccount::showDetails() const {
    Account::showDetails();
    std::cout << "Interest Rate: " << std::fixed << std::setprecision(2) << interestRate << "%\n";
}

std::string SavingsAccount::getAccountType() const {
    return "Savings";
}
