#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<bits/stdc++.h>
using namespace std;

class Account{
protected:
    int accountNumber;
    string name;
    double balance;
    vector<string> transactionHistory;

    void addTransaction(string transaction);

public:
    Account(int accountNumber,string name,double balance);
    virtual ~Account(){}

    int getAccountNumber();
    string getName();
    double getBalance();
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual bool transfer(Account& receiver,double amount);
    virtual void showDetails();
    virtual string getAccountType();

    void showTransactionHistory();
};

#endif
