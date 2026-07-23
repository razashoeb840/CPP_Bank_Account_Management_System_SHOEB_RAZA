#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
protected:
    int accountNumber;
    std::string name;
    double balance;
    std::vector<std::string> transactionHistory;

    void addTransaction(const std::string& transaction);

public:
    Account(int accountNumber, const std::string& name, double balance);
    virtual ~Account() = default;

    int getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual bool transfer(Account& receiver, double amount);
    virtual void showDetails() const;
    virtual std::string getAccountType() const;

    void showTransactionHistory() const;
};

#endif
