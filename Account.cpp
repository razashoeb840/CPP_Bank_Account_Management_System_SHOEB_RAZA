#include "Account.h"

#include <iomanip>
#include <iostream>
#include <sstream>

Account::Account(int accountNumber, const std::string& name, double balance)
    : accountNumber(accountNumber), name(name), balance(balance) {
    std::ostringstream message;
    message << "Account created with balance " << std::fixed << std::setprecision(2) << balance;
    addTransaction(message.str());
}

void Account::addTransaction(const std::string& transaction) {
    transactionHistory.push_back(transaction);
}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getName() const {
    return name;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid deposit amount.\n";
        return;
    }

    balance += amount;

    std::ostringstream message;
    message << "Deposited " << std::fixed << std::setprecision(2) << amount;
    addTransaction(message.str());

    std::cout << "Amount deposited successfully.\n";
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid withdrawal amount.\n";
        return false;
    }

    if (amount > balance) {
        std::cout << "Insufficient balance.\n";
        return false;
    }

    balance -= amount;

    std::ostringstream message;
    message << "Withdrawn " << std::fixed << std::setprecision(2) << amount;
    addTransaction(message.str());

    std::cout << "Amount withdrawn successfully.\n";
    return true;
}

bool Account::transfer(Account& receiver, double amount) {
    if (&receiver == this) {
        std::cout << "Cannot transfer to the same account.\n";
        return false;
    }

    if (!withdraw(amount)) {
        return false;
    }

    receiver.balance += amount;

    std::ostringstream senderMessage;
    senderMessage << "Transferred " << std::fixed << std::setprecision(2) << amount
                  << " to account " << receiver.getAccountNumber();
    addTransaction(senderMessage.str());

    std::ostringstream receiverMessage;
    receiverMessage << "Received " << std::fixed << std::setprecision(2) << amount
                    << " from account " << accountNumber;
    receiver.addTransaction(receiverMessage.str());

    std::cout << "Amount transferred successfully.\n";
    return true;
}

void Account::showDetails() const {
    std::cout << "\nAccount Number: " << accountNumber
              << "\nName: " << name
              << "\nAccount Type: " << getAccountType()
              << "\nBalance: " << std::fixed << std::setprecision(2) << balance << "\n";
}

std::string Account::getAccountType() const {
    return "General";
}

void Account::showTransactionHistory() const {
    std::cout << "\nTransaction History for Account " << accountNumber << ":\n";

    if (transactionHistory.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }

    for (const std::string& transaction : transactionHistory) {
        std::cout << transaction << "\n";
    }
}
